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
    auto rgb2xyz = []( const float x ) -> float {
        return ( x <= 0.04045f ) ?
            ( x / 12.92f ) :
            ( std::powf( ( x + 0.055f ) / 1.055f, 2.4f ) );
    };

    col_t sxyz;
    sxyz.x = rgb2xyz( rgb.x );
    sxyz.y = rgb2xyz( rgb.y );
    sxyz.z = rgb2xyz( rgb.z );

    col_t xyz;
    xyz.x = glm::dot( { 0.4124564f, 0.3575761f, 0.1804375f }, sxyz );
    xyz.y = glm::dot( { 0.2126729f, 0.7151522f, 0.0721750f }, sxyz );
    xyz.z = glm::dot( { 0.0193339f, 0.1191920f, 0.9503041f }, sxyz );

    xyz = xyz / xyz_ref;

    return xyz;
}


}   //  ::vivid::ciexyz
