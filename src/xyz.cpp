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

    return xyz;
}


////////////////////////////////////////////////////////////////////////////////
//  rgb \in [ 0, 1 ]
//  xyz \in [ 0, 1 ]
col_t fromRgb( const col_t& rgb )
{
    auto srgb2xyz = []( const float x ) -> float {
        return ( x <= 0.04045f ) ?
            ( x / 12.92f ) :
            ( std::powf( ( x + 0.055f ) / 1.055f, 2.4f ) );
    };

    col_t sxyz;
    sxyz.x = srgb2xyz( rgb.x );
    sxyz.y = srgb2xyz( rgb.y );
    sxyz.z = srgb2xyz( rgb.z );

    col_t xyz = matrices::srgb_to_xyz * sxyz;
    xyz = xyz / ref_d65;

    return xyz;
}


////////////////////////////////////////////////////////////////////////////////
col_t fromAdobe( const col_t& adobe ) {
    col_t lrgb = glm::pow( adobe, glm::vec3( adobe::gamma ) );
    return matrices::adobe_to_xyz * lrgb;
}



}   //  ::vivid::xyz
