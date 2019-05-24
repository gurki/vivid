#pragma once

#include "vivid/types.h"

namespace vivid {


class Color;

rgb_t lerp( const rgb_t&, const rgb_t&, const float );
hsl_t lerp( const hsl_t&, const hsl_t&, const float );
hsv_t lerp( const hsv_t&, const hsv_t&, const float );
lch_t lerp( const lch_t&, const lch_t&, const float );

Color lerpRgb( const Color&, const Color&, const float );
Color lerpHsv( const Color&, const Color&, const float );
Color lerpHsl( const Color&, const Color&, const float );
Color lerpLch( const Color&, const Color&, const float );   //  NOTE: saturates


}   //  ::vivid
