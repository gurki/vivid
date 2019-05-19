#pragma once

#include "vivid/types.h"
#include "vivid/colormap.h"
#include <string>


namespace vivid {


void printColorTable(
    const bool foreground = true,
    const bool background = true
);


namespace rgb
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


namespace srgb
{
    //  non-simplified compunding
    float comp( const float k );
    float invComp( const float k );

    col_t fromLinear( const col_t& lrgb );
    col_t toLinear( const col_t& srgb );
}


namespace hsv {
    col_t lerp( const col_t&, const col_t&, const float );
}


namespace lch {
    col_t lerp( const col_t&, const col_t&, const float );
}


namespace hsl
{
    col_t lerp( const col_t&, const col_t&, const float );

    col_t rainbow(
        const uint8_t k,
        const float s = 1.f,
        const float l = 0.5f
    );
}


namespace ansi {
    std::string colorize( const std::string& text, const ColorMap& cmap );
}


}   //   ::vivid
