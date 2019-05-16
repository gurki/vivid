#include "vivid/colortable.h"
#include "vivid/conversion.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <ios>      //  std::hex
#include <string_view>
#include <regex>
#include <cctype>   //  std::tolower


namespace tq {


nlohmann::json ColorTable::table_ = {};
ColorTable ColorTable::instance_ = {};
std::unordered_map<uint32_t, uint8_t> ColorTable::lookup_ = {};


////////////////////////////////////////////////////////////////////////////////
void ColorTable::initialize() {
    load( VIVID_ROOT_PATH "/res/colors.json" );
}


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
        const auto rgb3b = rgb8( uint8_t( id ) );
        const auto rgb32 = rgb32::fromRgb8( rgb3b );
        lookup_[ rgb32 ] = uint8_t( id );
    }

    return ! empty();
}


////////////////////////////////////////////////////////////////////////////////
std::string ColorTable::hex( const uint8_t index ) {
    assert( ! empty() );
    return table_.at( index ).at( "hexString" );
}


////////////////////////////////////////////////////////////////////////////////
std::string ColorTable::name( const uint8_t index )  {
    assert( ! empty() );
    return table_.at( index ).at( "name" );
}


////////////////////////////////////////////////////////////////////////////////
col8_t ColorTable::rgb8( const uint8_t index ) {
    assert( ! empty() );
    const auto& arr = table_.at( index ).at( "rgb" );
    return col8_t( arr[ "r" ], arr[ "g" ], arr[ "b" ] );
}


////////////////////////////////////////////////////////////////////////////////
col_t ColorTable::hsl( const uint8_t index )
{
    assert( ! empty() );

    const auto& arr = table_.at( index ).at( "hsl" );

    return col_t(
        arr[ "h" ].get<uint8_t>() / 360.f,
        arr[ "s" ].get<uint8_t>() / 100.f,
        arr[ "l" ].get<uint8_t>() / 100.f
    );
}


////////////////////////////////////////////////////////////////////////////////////
std::optional<uint8_t> ColorTable::findRgb32( const uint32_t rgb32 )
{
    const auto it = lookup_.find( rgb32 );

    if ( it == lookup_.end() ) {
        return {};
    }

    return it->second;
}


////////////////////////////////////////////////////////////////////////////////////
std::optional<uint8_t> ColorTable::findName( const std::string& name )
{
    static auto iequals = []( const std::string& a, const std::string& b ) -> bool
    {
        return std::equal(
            a.begin(), a.end(),
            b.begin(), b.end(),
            []( char a, char b ) {
                return std::tolower( a ) == std::tolower( b );
            }
        );
    };

    const auto iter = std::find_if(
        table_.begin(), table_.end(),
        [ &name ]( const auto& entry ) {
            return iequals( entry[ "name" ], name );
        }
    );

    if ( iter == table_.end() ) {
        return {};
    }

    return iter.value()[ "colorId" ];
}


////////////////////////////////////////////////////////////////////////////////////
//  layout by gawin's kool xterm color demo
//  [7] https://github.com/gawin/bash-colors-256
void printColorTable( const bool foreground, const bool background )
{
    std::cout << std::endl;

    auto escapeCode = [=]( const uint8_t& id ) -> std::string
    {
        char idstr[ 4 ];
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
                const uint32_t val = uint32_t( ( r8 << 16 ) + ( g8 << 8 ) + b8 );

                std::cout << escapeCode( index::fromRgb( rgb::fromRgb32( val ) ));
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


}   //  ::tq
