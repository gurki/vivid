#pragma once

#include "vivid/types.h"
#include <string>
#include <optional>

namespace vivid {


//  lab \in [ ( 0, -86.1827, -107.86 ), ( 100, 98.2343, 94.478 ) ]
namespace lab {
    col_t fromXyz( const col_t& );
    col_t fromLch( const col_t& );
}


//  L*C*h(ab) \in [ ( 0, 0, -2 PI ), ( 100, 133.808, 2 PI ) ]
namespace lch {
    col_t fromLab( const col_t& );
    col_t fromRgb( const col_t& );  //  (-)
    col_t fromXyz( const col_t& );  //  (-)
}


//  hsv \in [0; 1]
namespace hsv {
    col_t fromHsl( const col_t& );  //  (-)
    col_t fromRgb( const col_t& );
}


//  hsl \in [0; 1]
namespace hsl {
    col_t fromIndex( const uint8_t );   //  *
    col_t fromHsv( const col_t& );      //  (-)
    col_t fromRgb( const col_t& );
}


//  rgb \in [0; 1]
namespace rgb
{
    col_t fromRgb8( const col8_t& );
    col_t fromRgb32( const uint32_t );      //  (-)
    col_t fromAdobe( const col_t& );        //  (-)
    col_t fromHsv( const col_t& );
    col_t fromHsl( const col_t& );
    col_t fromXyz( const col_t& );          //  to sRGB
    col_t fromLch( const col_t& );          //  (-)
    col_t fromHex( const std::string& );    //  (-)
    col_t fromIndex( const uint8_t );       //  (-)
    col_t fromName( const std::string& );   //  NOTE: fails silently with return black
}


//  adobe rgb
namespace adobe {
    static const float gamma = 2.19921875f;
    col_t fromRgb( const col_t& );  //  (-)
    col_t fromXyz( const col_t& );
}


//  rgb8 \in [0;255]
namespace rgb8 {
    col8_t fromRgb( const col_t& );
    col8_t fromRgb32( const uint32_t );
    col8_t fromIndex( const uint8_t );      //  *
    col8_t fromName( const std::string& );  //  NOTE: fails silently with return black
    col8_t fromHex( const std::string& );   //  (-)
}


//  rgb32 as 0xffRRGGBB
namespace rgb32 {
    uint32_t fromRgb( const col_t& );       //  (-)
    uint32_t fromRgb8( const col8_t& );
    uint32_t fromHex( const std::string& );
}


//  ansi color index (for use in e.g. ansi escape codes)
namespace index {
    uint8_t fromRgb( const col_t& );        //  (-)
    uint8_t fromRgb8( const col8_t& );      //  *
    uint8_t fromHsl( const col_t& );        //  (-)
    uint8_t fromHex( const std::string& );  //  (-)
    std::optional<uint8_t> fromName( const std::string& );
}


//  hex string
namespace hex {
    std::string fromRgb( const col_t& );    //  (-)
    std::string fromRgb8( const col8_t& );
    std::string fromRgb32( const uint32_t );
    std::string fromIndex( const uint8_t ); //  *
}


//  (nearest) xterm color name
namespace name {
    const std::string& fromRgb( const col_t& );    //  (-)
    const std::string& fromIndex( const uint8_t );
}


//  xyz \in [ ( 0, 0, 0 ), ( 1, 1, 1 ) ]
namespace xyz
{
    //  observer 2°, illuminant D65, sRGB
    static const col_t ref_d65 = { 0.95047f, 1.f, 1.08883f };

    col_t fromLab( const col_t& );
    col_t fromRgb( const col_t& );  //  assumes sRGB
    col_t fromLch( const col_t& );  //  (-)
    col_t fromAdobe( const col_t& );
}


namespace matrices
{
    //  NOTE(tgurdan):
    //    for readability, these are all initialized transposed due to
    //    column-major order. must post-multiply colors accordingly.

    //  srgb <-> xyz, d65

    static const glm::mat3 xyz_to_rgb = {
         3.2404542f,-1.5371385f,-0.4985134f,
        -0.9692600f, 1.8760108f, 0.0415560f,
         0.0556434f,-0.2040259f, 1.0572252f
    };

    static const glm::mat3 rgb_to_xyz = {
        0.4124564f, 0.3575761f, 0.1804375f,
        0.2126729f, 0.7151522f, 0.0721750f,
        0.0193339f, 0.1191920f, 0.9503041f
    };

    //  adobe <-> xyz, d65

    static const glm::mat3 xyz_to_adobe = {
         2.0413690f,-0.5649464f,-0.3446944f,
        -0.9692660f, 1.8760108f, 0.0415560f,
         0.0134474f,-0.1183897f, 1.0154096f,
    };

    static const glm::mat3 adobe_to_xyz = {
        0.5767309f, 0.1855540f, 0.1881852f,
        0.2973769f, 0.6273491f, 0.0752741f,
        0.0270343f, 0.0706872f, 0.9911085f
    };
}


}   //  ::vivid
