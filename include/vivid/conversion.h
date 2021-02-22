#pragma once

#include "vivid/types.h"

#include <glm/mat3x3.hpp>
#include <optional>
#include <string>

namespace vivid {


namespace lab {
    lab_t fromXyz( const xyz_t& );
    lab_t fromLch( const lch_t& );
}


namespace lch {
    lch_t fromLab( const lab_t& );
    lch_t fromSrgb( const srgb_t& );
    lch_t fromXyz( const xyz_t& );
}


namespace hsv {
    hsv_t fromHsl( const hsl_t& );
    hsv_t fromRgb( const rgb_t& );
}


namespace hsl {
    hsl_t fromIndex( const uint8_t );
    hsl_t fromHsv( const hsv_t& );
    hsl_t fromRgb( const rgb_t& );
}


namespace srgb {
    srgb_t fromLrgb( const lrgb_t& );
    srgb_t fromXyz( const xyz_t& );
    srgb_t fromLch( const lch_t& );
    srgb_t fromAdobe( const adobe_t& );
    srgb_t fromIndex( const uint8_t );
    srgb_t fromOklab( const oklab_t& );
    srgb_t fromName( const std::string& );  //  fails silently, returning black
}


namespace lrgb {
    lrgb_t fromSrgb( const srgb_t& );
    lrgb_t fromRgb( const rgb_t&, const float gamma );
    lrgb_t fromOklab( const oklab_t& );
}


namespace rgb
{
    rgb_t fromRgb8( const col8_t& );
    rgb_t fromRgb32( const uint32_t );
    rgb_t fromHsv( const hsv_t& );
    rgb_t fromHsl( const hsl_t& );
    rgb_t fromHex( const std::string& );
}


namespace adobe {
    adobe_t fromSrgb( const srgb_t& );
    adobe_t fromXyz( const xyz_t& );
}


namespace rgb8 {
    col8_t fromRgb( const rgb_t& );
    col8_t fromRgb32( const uint32_t );
    col8_t fromIndex( const uint8_t );
    col8_t fromName( const std::string& );  //  fails silently, returning black
    col8_t fromHex( const std::string& );
}


namespace rgb32 {
    uint32_t fromRgb( const rgb_t& );
    uint32_t fromRgb8( const col8_t& );
    uint32_t fromHex( const std::string& );
}


namespace index {
    uint8_t fromRgb( const rgb_t& );
    uint8_t fromRgb8( const col8_t& );
    uint8_t fromHsl( const hsl_t& );
    uint8_t fromHex( const std::string& );
    std::optional<uint8_t> fromName( const std::string& );
}


namespace hex {
    std::string fromRgb( const rgb_t& );
    std::string fromRgb8( const col8_t& );
    std::string fromRgb32( const uint32_t );
    std::string fromIndex( const uint8_t );
}


namespace name {
    const std::string& fromRgb( const rgb_t& ); //  clamps to nearest
    const std::string& fromIndex( const uint8_t );
}


namespace xyz {
    xyz_t fromLab( const lab_t& );
    xyz_t fromSrgb( const srgb_t& );
    xyz_t fromLch( const lch_t& );  //  (-)
    xyz_t fromAdobe( const adobe_t& );
}


namespace oklab {
    oklab_t fromSrgb( const srgb_t& );
    oklab_t fromLrgb( const lrgb_t& );
}


}   //  ::vivid
