#pragma once

#include "vivid/types.h"
#include "vivid/colormap.h"
#include <string>


namespace vivid::rgb
{
    col_t lerp( const col_t&, const col_t&, const float );
    col_t lerpHsv( const col_t&, const col_t&, const float );
    col_t lerpHsl( const col_t&, const col_t&, const float );
    col_t lerpLch( const col_t&, const col_t&, const float );

    col_t saturate( const col_t& );
    col_t clamp( const col_t& );
    col_t rainbow( const uint8_t k );
    col_t gamma( const col_t&, const float );
    col_t invGamma( const col_t&, const float );
}


namespace vivid::srgb
{
    //  non-simplified compunding
    float comp( const float k );
    float invComp( const float k );

    col_t fromLinear( const col_t& lrgb );
    col_t toLinear( const col_t& srgb );
}


namespace vivid::hsv {
    col_t lerp( const col_t&, const col_t&, const float );
}


namespace vivid::lch {
    col_t lerp( const col_t&, const col_t&, const float );
}


namespace vivid::hsl
{
    col_t lerp( const col_t&, const col_t&, const float );

    col_t rainbow(
        const uint8_t k,
        const float s = 1.f,
        const float l = 0.5f
    );
}


namespace vivid::ansi {
    std::string colorize( const std::string& text, const ColorMap& cmap );
}
