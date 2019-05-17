#pragma once

#include "vivid/types.h"
#include "vivid/colormap.h"
#include <string>


namespace vivid::rgb
{
    col_t lerp( const col_t&, const col_t&, const float );
    col_t lerpHsv( const col_t&, const col_t&, const float );
    col_t lerpHsl( const col_t&, const col_t&, const float );
    col_t lerpHcl( const col_t&, const col_t&, const float );

    col_t saturate( const col_t& );
    col_t clamp( const col_t& );
    col_t rainbow( const uint8_t k );
}

namespace vivid::hsv {
    col_t lerp( const col_t&, const col_t&, const float );
}

namespace vivid::hcl {
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
