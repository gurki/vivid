#include "vivid/conversion.h"
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
//  rgb \in [ 0, 1 ]
//  xyz \in [ 0, 1 ]
col_t fromRgb( const col_t& rgb )
{
    //  inverse sRGB companding
    static const auto invComp = []( const float x ) -> float {
        return ( x <= 0.04045f ) ?
            ( x / 12.92f ) :
            ( std::powf( ( x + 0.055f ) / 1.055f, 2.4f ) );
    };

    col_t lrgb;
    lrgb.x = invComp( rgb.x );
    lrgb.y = invComp( rgb.y );
    lrgb.z = invComp( rgb.z );

    return lrgb * matrices::rgb_to_xyz;
}


////////////////////////////////////////////////////////////////////////////////
col_t fromAdobe( const col_t& adobe ) {
    col_t lrgb = glm::pow( adobe, glm::vec3( adobe::gamma ) );
    return lrgb * matrices::adobe_to_xyz;
}



}   //  ::vivid::xyz
