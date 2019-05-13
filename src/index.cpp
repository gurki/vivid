#include "vivid/conversion.h"
#include "vivid/colortable.h"
#include <glm/common.hpp>

namespace tq::index {


//////////////////////////////////////////////////////////////////////////////////
uint8_t fromRGB888( const colu8_t& rgb888 )
{
    //  direct match

    const auto rgbu32 = rgbu32::fromRGB888( rgb888 );

    if ( const auto res = ColorTable::findRGBu32( rgbu32 ) ) {
        return res.value();
    }

    //  snap to closest 6x6x6 rgb cube

    auto conv = []( const uint8_t v ) -> uint8_t {
        return uint8_t( std::roundf( 5.f * v / 255.f ) );
    };

    const auto r = conv( rgb888.x );
    const auto g = conv( rgb888.y );
    const auto b = conv( rgb888.z );

    return ( 16 + 36 * r + 6 * g + b );
}


//////////////////////////////////////////////////////////////////////////////////
uint8_t fromRGB( const col_t& rgb ) {
    return index::fromRGB888( rgb888::fromRGB( rgb ) );
}


}   //  ::tq::ansi
