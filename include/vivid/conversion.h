#pragma once

//  rgb \in [ ( 0, 0, 0 ), ( 1, 1, 1 ) ]
//  hsv \in [ ( 0, 0, 0 ), ( 1, 1, 1 ) ]
//  xyz \in [ ( 0, 0, 0 ), ( 1, 1, 1 ) ]
//  lab \in [ ( 0, -86.1827, -107.86 ), ( 100, 98.2343, 94.478 ) ]
//  lch \in [ ( 0, 0, -2 PI ), ( 100, 133.808, 2 PI ) ]

//  [1] http://www.easyrgb.com/index.php?X=MATH&H=08#text8
//  [2] https://www.cs.rit.edu/~ncs/color/t_convert.html
//  [3] http://docs.opencv.org/3.1.0/de/d25/imgproc_color_conversions.html#gsc.tab=0
//  [4] https://github.com/mbostock/d3/blob/master/src/color/rgb.js

#include <glm/vec3.hpp>

namespace tq {


using col_t = glm::vec3;
using col8_t = glm::vec<3, uint8_t>;


namespace ciexyz {
    col_t fromCIELab( const col_t& lab );
    col_t fromRGB( const col_t& rgb );
}

namespace cielab {
    col_t fromCIEXYZ( const col_t& xyz );
    col_t fromCIELCh( const col_t& lch );
}

namespace cielch {
    col_t fromCIELab( const col_t& lab );
    col_t fromRGB( const col_t& rgb );    //  convenience function
}

namespace hsv {
    col_t fromRGB( float r, float g, float b );
    col_t fromRGB( const col_t& rgb);
}

namespace rgb
{
    col_t fromRGB8( const col8_t& rgb8 );
    col_t fromHSV( float h, float s, float v );
    col_t fromHSV( const col_t& hsv );
    col_t fromCIEXYZ( const col_t& xyz );
    col_t fromCIELCh( const col_t& lch );  //  convenience function

    col_t lerpHSV( const col_t& rgb1, const col_t& rgb2, const float t );
    col_t lerpCIELCh( const col_t& rgb1, const col_t& rgb2, const float t );

    col_t saturate( const col_t& rgb );
    col_t rainbow( const int c );

    col_t spaceRoundtrip( const col_t& rgb );
    col_t typeRoundtrip( const col_t& rgb );
}

namespace rgb8 {
    col8_t fromRGB( const col_t& rgb );
}


}   //  ::tq
