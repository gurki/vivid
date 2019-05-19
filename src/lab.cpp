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

    const auto xyzr = xyz / xyz::ref_d65;

    col_t fxyz;
    fxyz.x = xyz2lab( xyzr.x );
    fxyz.y = xyz2lab( xyzr.y );
    fxyz.z = xyz2lab( xyzr.z );

    col_t lab;
    lab.x = 116.f * fxyz.y - 16.f;
    lab.y = 500.f * ( fxyz.x - fxyz.y );
    lab.z = 200.f * ( fxyz.y - fxyz.z );

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
