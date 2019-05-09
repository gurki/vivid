#include "vivid/conversion.h"


namespace tq::ansi {


//////////////////////////////////////////////////////////////////////////////////
uint8_t fromRGB( const col_t& rgb )
{
    auto conv = []( const uint8_t v ) -> uint8_t {
        return uint8_t( std::roundf( 5.f * v / 255.f ) );
    };

    const auto rgb888 = rgb888::fromRGB( rgb );
    const auto r = conv( rgb888.x );
    const auto g = conv( rgb888.y );
    const auto b = conv( rgb888.z );

    return ( 16 + 36 * r + 6 * g + b );
}


}   //  ::tq::ansi
