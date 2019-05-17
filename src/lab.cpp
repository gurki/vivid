#include "vivid/conversion.h"
#include <cmath>

namespace vivid::lab {


////////////////////////////////////////////////////////////////////////////////
//  xyz \in [ 0, 1 ]
//  l \in [ 0, 100 ]
//  ab \in [ -128, 128 ]
col_t fromXyz( const col_t& xyz )
{
    auto xyz2lab = []( const float x ) -> float {
        return ( x > 0.008856f ) ?
            std::cbrtf( x ) :
            ( 7.787f * x + 16.f / 116.f );
    };

    col_t sxyz;
    sxyz.x = xyz2lab( xyz.x );
    sxyz.y = xyz2lab( xyz.y );
    sxyz.z = xyz2lab( xyz.z );

    col_t lab;
    lab.x = 116.f * sxyz.y - 16.f;
    lab.y = 500.f * ( sxyz.x - sxyz.y );
    lab.z = 200.f * ( sxyz.y - sxyz.z );

    return lab;
}


////////////////////////////////////////////////////////////////////////////////
col_t fromHcl( const col_t& hcl )
{
    col_t lab;
    lab.x = hcl.z;
    lab.y = std::cosf( hcl.x ) * hcl.y;
    lab.z = std::sinf( hcl.x ) * hcl.y;

    return lab;
}


}   //  ::vivid::cielab
