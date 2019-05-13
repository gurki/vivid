#pragma once

#include "vivid/types.h"
#include <string>

//  kudos to all you color enthusiasts out there on the internet :)
//  [1] http://www.easyrgb.com/index.php?X=MATH&H=08#text8
//  [2] https://www.cs.rit.edu/~ncs/color/t_convert.html
//  [3] http://docs.opencv.org/3.1.0/de/d25/imgproc_color_conversions.html#gsc.tab=0
//  [4] https://github.com/mbostock/d3/blob/master/src/color/rgb.js

namespace tq {


//  xyz \in [ ( 0, 0, 0 ), ( 1, 1, 1 ) ]
namespace ciexyz
{
    col_t fromCIELab( const col_t& lab );
    col_t fromRGB( const col_t& rgb );

    //  observer 2°, illuminant D65
    static const col_t xyz_ref = col_t( 0.95047f, 1.f, 1.08883f );
}


//  lab \in [ ( 0, -86.1827, -107.86 ), ( 100, 98.2343, 94.478 ) ]
namespace cielab {
    col_t fromCIEXYZ( const col_t& xyz );
    col_t fromCIELCh( const col_t& lch );
}


//  lch \in [ ( 0, 0, -2 PI ), ( 100, 133.808, 2 PI ) ]
namespace cielch {
    col_t fromCIELab( const col_t& lab );
    col_t fromRGB( const col_t& rgb );    //  convenience function
}


//  hsv \in [0; 1]
namespace hsv {
    col_t fromHSL( const col_t& hsl );
    col_t fromRGB( float r, float g, float b );
    col_t fromRGB( const col_t& rgb);
}


//  hsl \in [0; 1]
namespace hsl {
    col_t fromHSV( const col_t& hsv );
    col_t fromRGB( const col_t& rgb );
    col_t fromIndex( const uint8_t index );
}


//  rgb \in [0; 1]
namespace rgb
{
    col_t fromRGB888( const colu8_t& rgb888 );
    col_t fromRGBu32( const uint32_t rgbu32 );
    col_t fromHSV( float h, float s, float v );
    col_t fromHSV( const col_t& hsv );
    col_t fromHSL( const col_t& hsl );
    col_t fromCIEXYZ( const col_t& xyz );
    col_t fromCIELCh( const col_t& lch );  //  convenience function
    col_t fromHex( const std::string& hexStr );
    col_t fromIndex( const uint8_t index );
}


//  rgb888 \in [0;255]
namespace rgb888 {
    colu8_t fromRGB( const col_t& rgb );
    colu8_t fromIndex( const uint8_t index );
}


//  rgbu32 as 0xffRRGGBB
namespace rgbu32 {
    uint32_t fromRGB( const col_t& rgb );
    uint32_t fromRGB888( const colu8_t& rgb );
    uint32_t fromHex( const std::string& hexStr );
}


//  ansi color index (for use in e.g. ansi escape codes)
namespace index {
    uint8_t fromRGB( const col_t& rgb );
    uint8_t fromRGB888( const colu8_t& rgb888 );
}


//  hex string
namespace hex {
    std::string fromRGB888( const colu8_t& rgb888 );
    std::string fromIndex( const uint8_t index );
}


//  (nearest) xterm color name
namespace xterm {
    std::string fromRGB( const col_t& rgb );
    std::string fromIndex( const uint8_t index );
}


}   //  ::tq
