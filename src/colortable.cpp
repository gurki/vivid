#include "vivid/colortable.h"
#include "vivid/conversion.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <ios>  //  std::hex
#include <string_view>
#include <regex>


namespace tq {


nlohmann::json ColorTable::table_ = {};
ColorTable ColorTable::instance_ = {};
std::unordered_map<uint32_t, uint8_t> ColorTable::lookup_ = {};


////////////////////////////////////////////////////////////////////////////////
bool ColorTable::load( const std::string& path )
{
    std::ifstream fin( path );

    assert( fin.is_open() );

    try {
        table_ = nlohmann::json::parse( fin );
    } catch ( const std::exception& ) {
        table_ = {};
    }

    assert( table_.size() == 256 );

    lookup_.clear();

    for ( uint16_t id = 0; id < 255; id++ ) {
        const auto rgbu8 = rgb888( uint8_t( id ) );
        const auto rgbu32 = rgbu32::fromRGB888( rgbu8 );
        lookup_[ rgbu32 ] = id;
    }

    return ! empty();
}


////////////////////////////////////////////////////////////////////////////////
std::string ColorTable::hex( const uint8_t ansi ) {
    assert( ! empty() );
    return table_.at( ansi ).at( "hexString" );
}


////////////////////////////////////////////////////////////////////////////////
std::string ColorTable::name( const uint8_t ansi )  {
    assert( ! empty() );
    return table_.at( ansi ).at( "name" );
}


////////////////////////////////////////////////////////////////////////////////
col_t ColorTable::rgb( const uint8_t ansi ) {
    return rgb::fromRGB888( rgb888( ansi ) );
}


////////////////////////////////////////////////////////////////////////////////
colu8_t ColorTable::rgb888( const uint8_t ansi ) {
    assert( ! empty() );
    const auto& arr = table_.at( ansi ).at( "rgb" );
    return colu8_t( arr[ "r" ], arr[ "g" ], arr[ "b" ] );
}


////////////////////////////////////////////////////////////////////////////////
col_t  ColorTable::hsl( const uint8_t ansi )
{
    assert( ! empty() );

    const auto& arr = table_.at( ansi ).at( "hsl" );

    return col_t(
        arr[ "h" ].get<uint8_t>() / 360.f,
        arr[ "s" ].get<uint8_t>() / 100.f,
        arr[ "l" ].get<uint8_t>() / 100.f
    );
}


////////////////////////////////////////////////////////////////////////////////////
std::optional<uint8_t> ColorTable::findRGBu32( const uint32_t rgbu32 )
{
    const auto it = lookup_.find( rgbu32 );

    if ( it == lookup_.end() ) {
        return {};
    }

    return it->second;
}


////////////////////////////////////////////////////////////////////////////////////
//  layout by gawin's kool xterm color demo
//  [1] https://github.com/gawin/bash-colors-256
void ColorTable::printTestTable(
    const bool foreground,
    const bool background )
{
    std::cout << std::endl;

    auto escapeCode = [=]( const uint8_t& id ) -> std::string
    {
        char idstr[ 3 ];
        std::sprintf( idstr, "%03d", id );

        const std::string bgstr = "\x1b[48;5;" + std::to_string( id ) + "m\x1b[38;5;15m " + idstr + " \x1b[0m";
        const std::string fgstr = " \x1b[38;5;" + std::to_string( id ) + "m" + idstr + "\x1b[0m ";

        if ( ! background ) {
            return fgstr;
        }

        if ( ! foreground ) {
            return bgstr;
        }

        return bgstr + fgstr;
    };

    for ( uint8_t i = 0; i < 8; i++ ) {
        std::cout << escapeCode( i );
    }

    std::cout << std::endl;

    for ( uint8_t i = 8; i < 16; i++ ) {
        std::cout << escapeCode( i );
    }

    std::cout << std::endl;
    std::cout << std::endl;

    const size_t numSteps = 6;
    const float step = ( numSteps == 1 ) ? 255.f : ( 255.f / ( numSteps - 1 ) );

    for ( float r = 0.f; r <= 255.f; r += step )
    {
        const uint8_t r8 = uint8_t( std::round( r ) );

        for ( float g = 0.f; g <= 255.f; g += step )
        {
            const uint8_t g8 = uint8_t( std::round( g ) );

            for ( float b = 0.f; b <= 255.f; b += step )
            {
                const uint8_t b8 = uint8_t( std::round( b ) );
                const uint32_t val = ( r8 << 16 ) + ( g8 << 8 ) + b8;

                std::cout << escapeCode( ansi::fromRGB( rgb::fromRGBu32( val ) ));
            }

            std::cout << std::endl;
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;

    //  NOTE(tgurdan): uint8_t causes endless loop here
    for ( uint16_t i = 232; i <= 255; i++ )
    {
        std::cout << escapeCode( uint8_t( i ) );

        if ( i % 6 == 3 ) {
            std::cout << std::endl;
        }
    }

    std::cout << std::endl << std::endl;
}


////////////////////////////////////////////////////////////////////////////////////
//Color::Color( const uint8_t index ) :
//    id_( index )
//{}


////////////////////////////////////////////////////////////////////////////////////
//Color::Color( const std::string& hexOrName )
//{
//    //  try hex
//    std::regex re( "^#((?:[0-9a-fA-F]{3}){1,2})$" );
//    std::smatch match;
//    std::regex_match( hexOrName, match, re );

//    //  revert to name
//    if ( match.empty() ) {
//        id_ = ColorTable::findName( hexOrName );
//        return;
//    }

//    //  parse hex

//    std::stringstream ss;
//    const std::string& hexstr = match[ 1 ];

//    ss << std::hex;

//    if ( hexstr.size() == 3 )  {
//        //  unpack 3-digit hex
//        for ( const auto& c : hexstr ) {
//            ss << c << c;
//        }
//    } else {
//        ss << hexstr;
//    }

//    uint32_t rgba;
//    ss >> rgba;

//    id_ = fromRGBA( rgba );
//}


////////////////////////////////////////////////////////////////////////////////////
//std::string Color::hex() const {
//    return ColorTable::hex( id_ );
//}


////////////////////////////////////////////////////////////////////////////////////
//std::string Color::name() const {
//    return ColorTable::name( id_ );
//}


////////////////////////////////////////////////////////////////////////////////////
//uint8_t Color::fromRGBA( const uint32_t rgba )
//{
//    auto conv = []( const int v ) -> int {
//        return int( std::roundf( 5.f * v / 255.f ) );
//    };

//    const int r = conv( ( rgba >> 16 ) & 0xff );
//    const int g = conv( ( rgba >> 8 ) & 0xff );
//    const int b = conv( rgba & 0xff  );

//    return ( 16 + 36 * r + 6 * g + b );
//}


}   //  mc
