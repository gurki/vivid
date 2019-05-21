#pragma once

#include "vivid/types.h"

namespace vivid {


rgb_t lerp( const rgb_t&, const rgb_t&, const float );
hsl_t lerp( const hsl_t&, const hsl_t&, const float );
hsv_t lerp( const hsv_t&, const hsv_t&, const float );
lch_t lerp( const lch_t&, const lch_t&, const float );

rgb_t lerpHsv( const rgb_t&, const rgb_t&, const float );
rgb_t lerpHsl( const rgb_t&, const rgb_t&, const float );
srgb_t lerpLch( const srgb_t&, const srgb_t&, const float );


}   //  ::vivid
