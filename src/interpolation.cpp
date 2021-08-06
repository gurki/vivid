#include "vivid/interpolation.h"
#include "vivid/conversion.h"
#include "vivid/color.h"
#include "vivid/utility.h"
#include "vivid/stream.h"

#include <iostream>

namespace vivid {


////////////////////////////////////////////////////////////////////////////////
rgb_t lerp( const rgb_t& rgb1, const rgb_t& rgb2, const float t ) {
    return static_cast<rgb_t>( rgb1 + t * ( rgb2 - rgb1 ) );
}


////////////////////////////////////////////////////////////////////////////////
hsl_t lerp( const hsl_t& hsl1, const hsl_t& hsl2, const float t )
{
    hsl_t hsl1a = hsl1;

    if ( std::abs( hsl1a.x - hsl2.x ) > 0.5f )
    {
        if( hsl1a.x > hsl2.x ) {
            hsl1a.x -= 1.f;
        } else {
            hsl1a.x += 1.f;
        }
    }

    auto hsl = hsl1a + t * ( hsl2 - hsl1a );
    hsl.x = std::fmod( hsl.x + 1.f, 1.f );

    return static_cast<hsl_t>( hsl );
}


////////////////////////////////////////////////////////////////////////////////
hsv_t lerp( const hsv_t& hsv1, const hsv_t& hsv2, const float t )
{
    hsv_t hsv1a = hsv1;

    if ( std::abs( hsv1a.x - hsv2.x ) > 0.5f )
    {
        if( hsv1a.x > hsv2.x ) {
            hsv1a.x -= 1.f;
        } else {
            hsv1a.x += 1.f;
        }
    }

    auto hsv = hsv1a + t * ( hsv2 - hsv1a );
    hsv.x = std::fmod( hsv.x + 1.f, 1.f );

    return static_cast<hsv_t>( hsv );
}


////////////////////////////////////////////////////////////////////////////////
lch_t lerp( const lch_t& lch1, const lch_t& lch2, const float t )
{
    col_t delta = lch2 - lch1;

    //  move along shortest path (wrap [0; 360])
    if ( delta.z > 180.f ) {
        delta.z -= 360.f;
    } else if ( delta.z < - 180.f ) {
        delta.z += 360.f;
    }

    auto interp = lch1 + t * delta;

    //  project back to [0; 360]
    interp.z = std::fmod( interp.z + 360.f, 360.f );
    return static_cast<lch_t>( interp );
}


////////////////////////////////////////////////////////////////////////////////
oklab_t lerp( const oklab_t& col1, const oklab_t& col2, const float t ) {
    return static_cast<oklab_t>( col1 + t * ( col2 - col1 ) );
}


////////////////////////////////////////////////////////////////////////////////
Color lerp( const Color& col1, const Color& col2, const float t )
{
    if ( col1.space() != col2.space() ) {
        return {};
    }

    switch ( col1.space() )
    {
        case Color::Space::Rgb: return Color( lerp( col1.srgb_, col2.srgb_, t ), Color::Space::Rgb );
        case Color::Space::Hsl: return Color( lerp( col1.hsl_, col2.hsl_, t ), Color::Space::Hsl );
        case Color::Space::Hsv: return Color( lerp( col1.hsv_, col2.hsv_, t ), Color::Space::Hsv );
        case Color::Space::Lch: return Color( lerp( col1.lch_, col2.lch_, t ), Color::Space::Lch );
        case Color::Space::Oklab: return Color( lerp( col1.oklab_, col2.oklab_, t ), Color::Space::Oklab );
        default: return {};
    }
}


////////////////////////////////////////////////////////////////////////////////
Color lerpRgb( const Color& col1, const Color& col2, const float t ) {
    return lerp( col1.rgb(), col2.rgb(), t );
}


////////////////////////////////////////////////////////////////////////////////
Color lerpHsv( const Color& col1, const Color& col2, const float t ) {
    return lerp( col1.hsv(), col2.hsv(), t ).rgb();
}


////////////////////////////////////////////////////////////////////////////////
Color lerpHsl( const Color& col1, const Color& col2, const float t ) {
    return lerp( col1.hsl(), col2.hsl(), t ).rgb();
}


////////////////////////////////////////////////////////////////////////////////
Color lerpLch( const Color& col1, const Color& col2, const float t ) {
    return lerp( col1.lch(), col2.lch(), t ).rgb().saturated();
}


////////////////////////////////////////////////////////////////////////////////
Color lerpOklab( const Color& col1, const Color& col2, const float t ) {
    return lerp( col1.oklab(), col2.oklab(), t ).rgb().saturated();
}


////////////////////////////////////////////////////////////////////////////////
Color lerpLinearRgb( const Color& col1, const Color& col2, const float t ) {
    const lrgb_t lrgb = lerp( col1.linearRgb(), col2.linearRgb(), t );
    return srgb::fromLrgb( lrgb );
}


}   //  ::vivid
