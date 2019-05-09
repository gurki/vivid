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
col_t  ColorTable::rgb( const uint8_t ansi ) {
    assert( ! empty() );
    const std::array<uint8_t, 3>& arr = table_.at( ansi ).at( "rgb" );
    return col_t( arr[ 0 ], arr[ 1 ], arr[ 2 ] ) / 255.f;
}


////////////////////////////////////////////////////////////////////////////////
col_t  ColorTable::hsl( const uint8_t ansi ) {
    assert( ! empty() );
    const std::array<uint8_t, 3>& arr = table_.at( ansi ).at( "hsl" );
    return col_t( arr[ 0 ] / 255.f, arr[ 1 ] / 100.f, arr[ 2 ] / 100.f );
}


////////////////////////////////////////////////////////////////////////////////////
void ColorTable::printTestTable( const uint8_t numSteps )
{
    static const std::string sym = "\xe2\x97\x8f";

    if ( numSteps == 0 ) {
        return;
    }

    std::cout << std::endl;

    auto escapeCode = []( const uint8_t& id ) -> std::string {
       return "\x1b[38;5;" + std::to_string( id ) + "m";
    };

    for ( uint8_t i = 0; i < 8; i++ ) {
        std::cout << escapeCode( i ) << sym;
    }

    std::cout << " ";
    std::cout << escapeCode( ansi::fromRGB( rgb::fromHex( "#000000" ) )) << sym;
    std::cout << escapeCode( ansi::fromRGB( rgb::fromHex( "#ff0000" ) )) << sym;
    std::cout << escapeCode( ansi::fromRGB( rgb::fromHex( "#00ff00" ) )) << sym;
    std::cout << escapeCode( ansi::fromRGB( rgb::fromHex( "#ffff00" ) )) << sym;
    std::cout << escapeCode( ansi::fromRGB( rgb::fromHex( "#0000ff" ) )) << sym;
    std::cout << escapeCode( ansi::fromRGB( rgb::fromHex( "#ff00ff" ) )) << sym;
    std::cout << escapeCode( ansi::fromRGB( rgb::fromHex( "#00ffff" ) )) << sym;
    std::cout << escapeCode( ansi::fromRGB( rgb::fromHex( "#ffffff" ) )) << sym;
    std::cout << std::endl;
    std::cout << std::endl;

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

                std::cout << escapeCode( ansi::fromRGB( rgb::fromRGBu32( val ) )) << sym;
            }

            std::cout << " ";
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;

    //  NOTE(tgurdan): uint8_t causes endless loop here
    for ( uint16_t i = 232; i <= 255; i++ ) {
        std::cout << escapeCode( uint8_t( i ) ) << sym;
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
