#include "vivid/functions.h"
#include "vivid/conversion.h"
#include "vivid/stream.h"
#include "vivid/encoding.h"
#include "vivid/colormap.h"

#include <glm/glm.hpp>
#include <glm/common.hpp>           //  clamp
#include <glm/gtc/constants.hpp>    //  pi
#include <glm/gtx/string_cast.hpp>

#include <iostream>
#include <sstream>

namespace vivid::rgb {


////////////////////////////////////////////////////////////////////////////////
col_t lerp( const col_t& rgb1, const col_t& rgb2, const float t ) {
    return glm::mix( rgb1, rgb2, t );
}


////////////////////////////////////////////////////////////////////////////////
col_t lerpHsv(
    const col_t& rgb1,
    const col_t& rgb2,
    const float t )
{
    col_t hsv1 = hsv::fromRgb( rgb1 );
    col_t hsv2 = hsv::fromRgb( rgb2 );
    return rgb::fromHsv( vivid::hsv::lerp( hsv1, hsv2, t ) );
}


////////////////////////////////////////////////////////////////////////////////
col_t lerpHsl(
    const col_t& rgb1,
    const col_t& rgb2,
    const float t )
{
    col_t hsl1 = hsl::fromRgb( rgb1 );
    col_t hsl2 = hsl::fromRgb( rgb2 );
    return rgb::fromHsl( vivid::hsl::lerp( hsl1, hsl2, t ) );
}


////////////////////////////////////////////////////////////////////////////////
col_t lerpHcl(
    const col_t& rgb1,
    const col_t& rgb2,
    const float t )
{
    col_t lch1 = hcl::fromRgb( rgb1 );
    col_t lch2 = hcl::fromRgb( rgb2 );
    return rgb::fromHcl( vivid::hcl::lerp( lch1, lch2, t ) );
}


////////////////////////////////////////////////////////////////////////////////
// input 0..255 for rainbow colors!
col_t rainbow( const uint8_t k )
{
    col_t col;

    if ( k < 42 ) {
        col.x = 255;
        col.y = float( k * 6 );
        col.z = 0;
    } else if ( k < 2 * 42 ) {
        col.x = float( 42 - ( k - 42 ) ) * 6;
        col.y = 255;
        col.z = 0;
    } else if ( k < 3 * 42 ) {
        col.x = 0;
        col.y = 255;
        col.z = float( k - 2 * 42 ) * 6;
    } else if ( k < 4 * 42 ) {
        col.x = 0;
        col.y = ( 42 - float( k - 3 * 42 ) ) * 6;
        col.z = 255;
    } else if ( k < 5 * 42 ) {
        col.x = float( k - 4 * 42 ) * 6;
        col.y = 0;
        col.z = 255;
    } else if ( k < 6 * 42 ) {
        col.x = 255;
        col.y = 0;
        col.z = ( 42 - float( k - 5 * 42 ) ) * 6;
    } else {
        col.x = 255;
        col.y = 0;
        col.z = 0;
    }

    return col / 255.0f;
}


////////////////////////////////////////////////////////////////////////////////
col_t saturate( const col_t& rgb )
{
    auto res = rgb;

    res.x = glm::clamp( rgb.x, 0.f, 1.f );
    res.y = glm::clamp( rgb.y, 0.f, 1.f );
    res.z = glm::clamp( rgb.z, 0.f, 1.f );

    return res;
}


////////////////////////////////////////////////////////////////////////////////
col_t clamp( const col_t& rgb ) {
    return vivid::rgb::fromIndex( vivid::index::fromRgb( rgb ) );
}


}   //  ::vivid::rgb


namespace vivid::srgb {


////////////////////////////////////////////////////////////////////////////////
float comp( const float k )
{
    if ( k <= 0.00304f ) {
        return 12.92f * k;
    }

    return 1.055f * std::pow( k, 1.f / 2.4f ) - 0.055f;
}


////////////////////////////////////////////////////////////////////////////////
float invComp( const float k )
{
    if ( k <= 0.04045f ) {
        return k / 12.92f;
    }

    return std::powf( ( k + 0.055f ) / 1.055f, 2.4f );
}


////////////////////////////////////////////////////////////////////////////////
col_t toLinear( const col_t& srgb )
{
    return {
        srgb::invComp( srgb.x ),
        srgb::invComp( srgb.y ),
        srgb::invComp( srgb.z )
    };
}


////////////////////////////////////////////////////////////////////////////////
col_t fromLinear( const col_t& lrgb )
{
    return {
        srgb::comp( lrgb.x ),
        srgb::comp( lrgb.y ),
        srgb::comp( lrgb.z )
    };
}


}   //   ::vivid::srgb


namespace vivid::hsl {

////////////////////////////////////////////////////////////////////////////////
col_t rainbow( const uint8_t k, const float s, const float l ) {
    const float t = k / 256.f;
    return { t, s, l };
}


////////////////////////////////////////////////////////////////////////////////
col_t lerp(
    const col_t& hsl1,
    const col_t& hsl2,
    const float t )
{
    col_t hsl1a = hsl1;

    if ( std::abs( hsl1a.x - hsl2.x ) > 0.5f )
    {
        if( hsl1a.x > hsl2.x ) {
            hsl1a.x -= 1.0f;
        } else {
            hsl1a.x += 1.0f;
        }
    }

    col_t hsl = glm::mix( hsl1a, hsl2, t );
    hsl.x = std::fmodf( hsl.x, 1.0f );

    return hsl;
}

}   //  ::vivid::hsl


namespace vivid::hsv {

////////////////////////////////////////////////////////////////////////////////
col_t lerp(
    const col_t& hsv1,
    const col_t& hsv2,
    const float t )
{
    col_t hsv1a = hsv1;

    if ( std::abs( hsv1a.x - hsv2.x ) > 0.5f )
    {
        if( hsv1a.x > hsv2.x ) {
            hsv1a.x -= 1.0f;
        } else {
            hsv1a.x += 1.0f;
        }
    }

    col_t hsv = glm::mix( hsv1a, hsv2, t );
    hsv.x = std::fmodf( hsv.x, 1.0f );

    return hsv;
}

}   //  ::vivid::hsv


namespace vivid::hcl {

////////////////////////////////////////////////////////////////////////////////
col_t lerp(
    const col_t& hcl1,
    const col_t& hcl2,
    const float t )
{
    col_t delta = hcl2 - hcl1;

    if ( delta.x > glm::pi<float>() ) {
        delta.x -= glm::two_pi<float>();
    } else if ( delta.x < - glm::pi<float>() ) {
        delta.x += glm::two_pi<float>();
    }

    return hcl1 + t * delta;
}

}   //  ::vivid::hcl


namespace vivid::ansi {

////////////////////////////////////////////////////////////////////////////////
std::string colorize( const std::string& text, const ColorMap& cmap )
{
    if ( cmap.empty() ) {
        return text;
    }

    const float n = float( text.size() );
    std::stringstream ss;

    for ( size_t i = 0; i < n; i++ ) {
        const float t = i / n;
        const uint8_t id = vivid::index::fromRgb( cmap.at( t ) );
        ss << vivid::ansi::fg( id ) << text[ i ];
    }

    ss << vivid::ansi::reset;
    return ss.str();
}

}   //  ::vivid::ansi
