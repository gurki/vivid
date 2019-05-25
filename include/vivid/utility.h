#pragma once

#include "vivid/types.h"
#include <string>

namespace vivid {


class ColorMap;


namespace rgb
{
    rgb_t saturate( const rgb_t& );
    rgb_t clamp( const rgb_t& );
    rgb_t gamma( const rgb_t&, const float );
    rgb_t grey( const uint8_t k );
}


namespace srgb {
    //  non-simplified compunding
    float compound( const float k );
    float inverseCompound( const float k );
}


namespace hsl
{
    static const glm::vec3 sup = { 360, 100, 100 };

    hsl_t rainbow(
        const uint8_t k,
        const float s = 1.f,
        const float l = 0.5f
    );

    hsl_t compact( const col_t& col );
    hsl_t readable( const col_t& col );
}


namespace hsv
{
    static const glm::vec3 sup = { 360, 100, 100 };

    hsv_t compact( const col_t& col );
    hsv_t readable( const col_t& col );
}


namespace xyz
{
    static const glm::vec3 sup = { 100, 100, 100 };

    xyz_t compact( const xyz_t& col );
    xyz_t readable( const xyz_t& col );
}


namespace lch {
    lch_t saturate( const lch_t& );
}


namespace ansi
{
    std::string colorize( const std::string& text, const ColorMap& cmap );
    std::string colorize( const col_t& col, const std::string& label );

    void printColorTable(
        const bool foreground = true,
        const bool background = true
    );

    void printColorPresets();
}






}   //   ::vivid
