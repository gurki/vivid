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
    rgb_t saturate( const rgb_t& );
    rgb_t clamp( const rgb_t& );
    rgb_t rainbow( const uint8_t k );
    rgb_t gamma( const rgb_t&, const float );
    rgb_t invGamma( const rgb_t&, const float );
}


namespace srgb {
    //  non-simplified compunding
    float compound( const float k );
    float inverseCompound( const float k );
}


namespace hsl
{
    rgb_t rainbow(
        const uint8_t k,
        const float s = 1.f,
        const float l = 0.5f
    );
}


namespace ansi
{
    std::string colorize(
        const std::string& text,
        const ColorMap& cmap
    );
}


}   //   ::vivid
