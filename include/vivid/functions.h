#pragma once

#include "vivid/types.h"


namespace tq::rgb
{
    col_t lerp( const col_t& rgb1, const col_t& rgb2, const float t );
    col_t lerpHsv( const col_t& rgb1, const col_t& rgb2, const float t );
    col_t lerpHsl( const col_t& rgb1, const col_t& rgb2, const float t );
    col_t lerpHcl( const col_t& rgb1, const col_t& rgb2, const float t );

    col_t saturate( const col_t& rgb );
    col_t clamp( const col_t& rgb );
    col_t rainbow( const int c );

    col_t spaceRoundtrip( const col_t& rgb );
    col_t typeRoundtrip( const col_t& rgb );
}
