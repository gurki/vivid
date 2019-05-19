#include "vivid/conversion.h"
#include "vivid/functions.h"
#include <glm/glm.hpp>

namespace vivid::xyz {


////////////////////////////////////////////////////////////////////////////////
col_t fromLab( const col_t& lab )
{
    col_t xyz;
    xyz.y = ( lab.x + 16.f ) / 116.f;
    xyz.x = xyz.y + lab.y / 500.0f;
    xyz.z = xyz.y - lab.z / 200.0f;

    auto lab2xyz = []( const float x ) -> float {
        return ( x > 0.206893034f ) ?
            ( x * x * x ) :
            ( ( x - 16.f / 116.f ) / 7.787037f );
    };

    xyz.x = lab2xyz( xyz.x );
    xyz.y = lab2xyz( xyz.y );
    xyz.z = lab2xyz( xyz.z );
    xyz = xyz * xyz::ref_d65;

    return xyz;
}


////////////////////////////////////////////////////////////////////////////////
col_t fromRgb( const col_t& rgb ) {
    return srgb::toLinear( rgb ) * matrices::rgb_to_xyz;
}


////////////////////////////////////////////////////////////////////////////////
col_t fromAdobe( const col_t& adobe ) {
    col_t lrgb = rgb::gamma( adobe, adobe::gamma );
    return lrgb * matrices::adobe_to_xyz;
}



}   //  ::vivid::xyz
