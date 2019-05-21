#include "vivid/interpolation.h"
#include "vivid/conversion.h"

namespace vivid {


////////////////////////////////////////////////////////////////////////////////
rgb_t lerp( const rgb_t& rgb1, const rgb_t& rgb2, const float t ) {
    return glm::mix( rgb1, rgb2, t );
}


////////////////////////////////////////////////////////////////////////////////
hsl_t lerp( const hsl_t& hsl1, const hsl_t& hsl2, const float t )
{
    hsl_t hsl1a = hsl1;

    if ( std::abs( hsl1a.x - hsl2.x ) > 0.5f )
    {
        if( hsl1a.x > hsl2.x ) {
            hsl1a.x -= 1.0f;
        } else {
            hsl1a.x += 1.0f;
        }
    }

    auto hsl = glm::mix( hsl1a, hsl2, t );
    hsl.x = std::fmodf( hsl.x, 1.0f );

    return hsl;
}


////////////////////////////////////////////////////////////////////////////////
hsv_t lerp( const hsv_t& hsv1, const hsv_t& hsv2, const float t )
{
    hsv_t hsv1a = hsv1;

    if ( std::abs( hsv1a.x - hsv2.x ) > 0.5f )
    {
        if( hsv1a.x > hsv2.x ) {
            hsv1a.x -= 1.0f;
        } else {
            hsv1a.x += 1.0f;
        }
    }

    auto hsv = glm::mix( hsv1a, hsv2, t );
    hsv.x = std::fmodf( hsv.x, 1.0f );

    return hsv;
}


////////////////////////////////////////////////////////////////////////////////
lch_t lerp( const lch_t& lch1, const lch_t& lch2, const float t )
{
    col_t delta = lch2 - lch1;

    //  move along shortest path (wrap [0; 360])
    if ( delta.z > 180.f ) {
        delta.z -= 360.f;
    } else if ( delta.z < - 180.f ) {
        delta.z += 380.f;
    }

    auto interp = lch1 + t * delta;

    //  project back to [0; 360]
    interp.z = std::fmodf( interp.z + 360.f, 360.f );
    return static_cast<lch_t>( interp );
}


////////////////////////////////////////////////////////////////////////////////
rgb_t lerpHsv(
    const rgb_t& rgb1,
    const rgb_t& rgb2,
    const float t )
{
    hsv_t hsv1 = hsv::fromRgb( rgb1 );
    hsv_t hsv2 = hsv::fromRgb( rgb2 );
    return rgb::fromHsv( lerp( hsv1, hsv2, t ) );
}


////////////////////////////////////////////////////////////////////////////////
rgb_t lerpHsl(
    const rgb_t& rgb1,
    const rgb_t& rgb2,
    const float t )
{
    hsl_t hsl1 = hsl::fromRgb( rgb1 );
    hsl_t hsl2 = hsl::fromRgb( rgb2 );
    return rgb::fromHsl( lerp( hsl1, hsl2, t ) );
}


////////////////////////////////////////////////////////////////////////////////
srgb_t lerpLch(
    const srgb_t& srgb1,
    const srgb_t& srgb2,
    const float t )
{
    lch_t lch1 = lch::fromSrgb( srgb1 );
    lch_t lch2 = lch::fromSrgb( srgb2 );
    return srgb::fromLch( lerp( lch1, lch2, t ) );
}


}   //  ::vivid
