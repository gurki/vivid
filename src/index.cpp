#include "vivid/conversion.h"
#include "vivid/data/xterm.h"
#include <glm/common.hpp>
#include <algorithm>

namespace vivid::index {


//////////////////////////////////////////////////////////////////////////////////
uint8_t fromRgb8( const col8_t& rgb8 )
{
    //  search direct match

    const auto rgb32 = rgb32::fromRgb8( rgb8 );
    const auto& tab = data::xterm_rgb32;
    const auto it = tab.find( rgb32 );

    if ( it != tab.end() ) {
        return it->second;
    }

    //  grey value

    if ( rgb8.x == rgb8.y && rgb8.y == rgb8.z ) {
        return data::xterm_grey.at( rgb8.x );
    }

    //  snap to closest 6x6x6 rgb cube

    auto conv = []( const uint8_t v ) -> uint8_t {
        return uint8_t( std::roundf( 5.f * v / 255.f ) );
    };

    const auto r = conv( rgb8.x );
    const auto g = conv( rgb8.y );
    const auto b = conv( rgb8.z );

    return ( 16 + 36 * r + 6 * g + b );
}


//////////////////////////////////////////////////////////////////////////////////
uint8_t fromRgb( const rgb_t& rgb ) {
    return index::fromRgb8( rgb8::fromRgb( rgb ) );
}


////////////////////////////////////////////////////////////////////////////////
uint8_t fromHsl( const hsl_t& hsl ) {
    return index::fromRgb( rgb::fromHsl( hsl ) );
}


////////////////////////////////////////////////////////////////////////////////
uint8_t fromHex( const std::string& hexStr ) {
    return index::fromRgb8( rgb8::fromHex( hexStr ) );
}


////////////////////////////////////////////////////////////////////////////////
std::optional<uint8_t> fromName( const std::string& name )
{
    auto key = name;
    std::transform( key.begin(), key.end(), key.begin(), ::tolower);

    const auto& tab = data::xterm_names;
    const auto it = tab.find( key );

    if ( it != tab.end() ) {
        return it->second;
    }

    return {};
}


}   //  ::vivid::index
