#pragma once

#include "vivid/types.h"
#include <string>

class ColorMap;


namespace tq::rgb
{
    col_t lerp( const col_t&, const col_t&, const float );
    col_t lerpHsv( const col_t&, const col_t&, const float );
    col_t lerpHsl( const col_t&, const col_t&, const float );
    col_t lerpHcl( const col_t&, const col_t&, const float );

    col_t saturate( const col_t& );
    col_t clamp( const col_t& );
    col_t rainbow( const uint8_t k );

    col_t spaceRoundtrip( const col_t& );
    col_t typeRoundtrip( const col_t& );
}

namespace tq::hsv {
    col_t lerp( const col_t&, const col_t&, const float );
}

namespace tq::hcl {
    col_t lerp( const col_t&, const col_t&, const float );
}

namespace tq::hsl
{
    col_t lerp( const col_t&, const col_t&, const float );

    col_t rainbow(
        const uint8_t k,
        const float s = 1.f,
        const float l = 0.5f
    );
}

namespace tq::ansi {
    std::string colorize( const std::string& text, const ColorMap& cmap );
}
