#include "vivid/conversion.h"
#include <cmath>

namespace tq::cielab {


////////////////////////////////////////////////////////////////////////////////
//  xyz \in [ 0, 1 ]
//  l \in [ 0, 100 ]
//  ab \in [ -128, 128 ]
//  [3] http://docs.opencv.org/3.1.0/de/d25/imgproc_color_conversions.html#gsc.tab=0
//  [4] https://github.com/mbostock/d3/blob/master/src/color/rgb.js
col_t fromCIEXYZ( const col_t& xyz )
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
col_t fromCIELCh( const col_t& lch)
{
    col_t lab;
    lab.x = lch.x;
    lab.y = std::cosf( lch.z ) * lch.y;
    lab.z = std::sinf( lch.z ) * lch.y;

    return lab;
}


}   //  ::tq::cielab
