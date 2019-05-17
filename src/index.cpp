#include "vivid/conversion.h"
#include "vivid/colortable.h"
#include <glm/common.hpp>

namespace vivid::index {


//////////////////////////////////////////////////////////////////////////////////
uint8_t fromRgb8( const col8_t& rgb8 )
{
    //  direct match

    const auto rgb32 = rgb32::fromRgb8( rgb8 );

    if ( const auto res = ColorTable::findRgb32( rgb32 ) ) {
        return res.value_or( 0 );
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
uint8_t fromRgb( const col_t& rgb ) {
    return index::fromRgb8( rgb8::fromRgb( rgb ) );
}


////////////////////////////////////////////////////////////////////////////////
uint8_t fromHsl( const col_t& hsl ) {
    return index::fromRgb( rgb::fromHsl( hsl ) );
}


////////////////////////////////////////////////////////////////////////////////
uint8_t fromHex( const std::string& hexStr ) {
    return index::fromRgb8( rgb8::fromHex( hexStr ) );
}


////////////////////////////////////////////////////////////////////////////////
uint8_t fromName( const std::string& name ) {
    return ColorTable::findName( name ).value_or( 0 );
}


}   //  ::vivid::index
