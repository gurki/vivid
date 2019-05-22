#pragma once

#include "vivid/types.h"

#include <glm/mat3x3.hpp>
#include <string>
#include <optional>

namespace vivid {


//  CIE L*a*b* \in [ (0, -86.1827, -107.86); (100, 98.2343, 94.478) ]
namespace lab {
    lab_t fromXyz( const xyz_t& );
    lab_t fromLch( const lch_t& );
}


//  CIE L*C*h(ab) \in [ (0, 0, 0); (100, 140, 360) ]
namespace lch {
    lch_t fromLab( const lab_t& );
    lch_t fromSrgb( const srgb_t& );
    lch_t fromXyz( const xyz_t& );  //  (-)
}


//  hsv \in [0; 1]
namespace hsv {
    hsv_t fromHsl( const hsl_t& );  //  (-)
    hsv_t fromRgb( const rgb_t& );
}


//  hsl \in [0; 1]
namespace hsl {
    hsl_t fromIndex( const uint8_t );   //  *
    hsl_t fromHsv( const hsv_t& );      //  (-)
    hsl_t fromRgb( const rgb_t& );
}


//  sRGB
namespace srgb {
    srgb_t fromLrgb( const lrgb_t& );
    srgb_t fromXyz( const xyz_t& );     //  to sRGB
    srgb_t fromLch( const lch_t& );     //  (-)
    srgb_t fromAdobe( const adobe_t& ); //  (-)
    srgb_t fromIndex( const uint8_t );       //  (-)
    srgb_t fromName( const std::string& );   //  NOTE: fails silently with return black
}


//  linear rgb
namespace lrgb {
    lrgb_t fromSrgb( const srgb_t& );
    lrgb_t fromRgb( const rgb_t&, const float gamma );
}


//  rgb \in [0; 1]
namespace rgb
{
    rgb_t fromRgb8( const col8_t& );
    rgb_t fromRgb32( const uint32_t );      //  (-)
    rgb_t fromHsv( const hsv_t& );
    rgb_t fromHsl( const hsl_t& );
    rgb_t fromHex( const std::string& );    //  (-)
}


//  adobe rgb
namespace adobe {
    static const float gamma = 2.19921875f;
    adobe_t fromSrgb( const srgb_t& );  //  (-)
    adobe_t fromXyz( const xyz_t& );
}


//  rgb8 \in [0;255]
namespace rgb8 {
    col8_t fromRgb( const rgb_t& );
    col8_t fromRgb32( const uint32_t );
    col8_t fromIndex( const uint8_t );      //  *
    col8_t fromName( const std::string& );  //  NOTE: fails silently with return black
    col8_t fromHex( const std::string& );   //  (-)
}


//  rgb32 as 0xffRRGGBB
namespace rgb32 {
    uint32_t fromRgb( const rgb_t& );       //  (-)
    uint32_t fromRgb8( const col8_t& );
    uint32_t fromHex( const std::string& );
}


//  ansi color index (for use in e.g. ansi escape codes)
namespace index {
    uint8_t fromRgb( const rgb_t& );        //  (-)
    uint8_t fromRgb8( const col8_t& );      //  *
    uint8_t fromHsl( const hsl_t& );        //  (-)
    uint8_t fromHex( const std::string& );  //  (-)
    std::optional<uint8_t> fromName( const std::string& );
}


//  hex string
namespace hex {
    std::string fromRgb( const rgb_t& );    //  (-)
    std::string fromRgb8( const col8_t& );
    std::string fromRgb32( const uint32_t );
    std::string fromIndex( const uint8_t ); //  *
}


//  (nearest) xterm color name
namespace name {
    const std::string& fromRgb( const rgb_t& );    //  (-)
    const std::string& fromIndex( const uint8_t );
}


//  CIE XYZ \in [ (0, 0, 0), ref_d65 ]
namespace xyz
{
    //  observer 2°, illuminant D65, sRGB
    static const xyz_t ref_d65 = { 0.95047f, 1.f, 1.08883f };

    xyz_t fromLab( const lab_t& );
    xyz_t fromSrgb( const srgb_t& );
    xyz_t fromLch( const lch_t& );  //  (-)
    xyz_t fromAdobe( const adobe_t& );
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
