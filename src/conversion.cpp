#include "vivid/conversion.h"

#include <glm/glm.hpp>
#include <glm/common.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/string_cast.hpp>

#include <iostream>

namespace tq {

//  observer = 2°, illuminant= D65
//  [1] http://www.easyrgb.com/index.php?X=MATH&H=08#text8
static const col_t xyz_ref = col_t( 0.95047f, 1.f, 1.08883f );


namespace rgb {


////////////////////////////////////////////////////////////////////////////////
col_t lerpHSV(
    const col_t& rgb1,
    const col_t& rgb2,
    const float t )
{
    col_t hsv1 = hsv::fromRGB( rgb1 );
    col_t hsv2 = hsv::fromRGB( rgb2 );

    col_t hsv;

    if ( std::abs( hsv1.x - hsv2.x ) > 0.5f )
    {
        if( hsv1.x > hsv2.x ) {
            hsv1.x -= 1.0f;
        } else {
            hsv1.x += 1.0f;
        }
    }

    hsv = glm::mix( hsv1, hsv2, t );
    hsv.x = std::fmodf( hsv.x, 1.0f );

    return rgb::fromHSV( hsv );
}


////////////////////////////////////////////////////////////////////////////////
col_t lerpCIELCh(
    const col_t& rgb1,
    const col_t& rgb2,
    const float t )
{
    col_t lch1 = cielch::fromRGB( rgb1 );
    col_t lch2 = cielch::fromRGB( rgb2 );

    col_t delta = lch2 - lch1;

    if ( delta.z > glm::pi<float>() ) {
        delta.z -= glm::two_pi<float>();
    } else if ( delta.z < - glm::pi<float>() ) {
        delta.z += glm::two_pi<float>();
    }

    col_t lch = lch1 + t * delta;

    return rgb::fromCIELCh( lch );
}


////////////////////////////////////////////////////////////////////////////////
// input 0..255 for rainbow colors!
col_t rainbow( const int c )
{
    const int k = c % 255;
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
col_t fromRGB8( const col8_t& rgb8 )
{
    col_t rgb;
    rgb.x = rgb8.x / 255.f;
    rgb.y = rgb8.y / 255.f;
    rgb.z = rgb8.z / 255.f;

    return rgb;
}


////////////////////////////////////////////////////////////////////////////////
//  h: [0, 1], s: [0, 1], v: [0, 1]
col_t fromHSV( float h, float s, float v )
{
    h = ( h > 0.f ) ? ( std::fmodf( h, 1.f ) ) : ( 1.f + std::fmodf( h, 1.f ) );   //  wrap
    s = glm::clamp( s, 0.f, 1.f );
    v = glm::clamp( v, 0.f, 1.f );

    col_t col;

    if( s == 0.f ) {
        col[ 0 ] = v;
        col[ 1 ] = v;
        col[ 2 ] = v;
    }
    else
    {
        const float k = h * 6.f;
        const int d = int( std::floorf( k ) );
        const float c = v * s;
        const float x = c * ( 1.f - std::fabsf( std::fmodf( k, 2.f ) - 1.f ) );

        switch( d )
        {
            case 0:  col = col_t( c, x, 0.f ); break;
            case 1:  col = col_t( x, c, 0.f ); break;
            case 2:  col = col_t( 0.f, c, x ); break;
            case 3:  col = col_t( 0.f, x, c ); break;
            case 4:  col = col_t( x, 0.f, c ); break;
            default: col = col_t( c, 0.f, x ); break;
        }

        const float m = v - c;
        col[ 0 ] += m;
        col[ 1 ] += m;
        col[ 2 ] += m;
    }

    return col;
}


////////////////////////////////////////////////////////////////////////////////
col_t fromHSV( const col_t& hsv ) {
    return rgb::fromHSV( hsv.x, hsv.y, hsv.z );
}


////////////////////////////////////////////////////////////////////////////////
col_t fromCIEXYZ( const col_t& xyz )
{
    auto xyz2rgb = []( const float x ) -> float {
        return ( x <= 0.00304f ) ?
            ( 12.92f * x ) :
            ( 1.055f * std::pow( x, 1.f / 2.4f ) - 0.055f );
    };

    const col_t sxyz = xyz * xyz_ref;

    col_t rgb = {};
    rgb.x = glm::dot( { 3.2404542f,-1.5371385f,-0.4985134f }, sxyz );
    rgb.y = glm::dot( {-0.9692600f, 1.8760108f, 0.0415560f }, sxyz );
    rgb.z = glm::dot( { 0.0556434f,-0.2040259f, 1.0572252f }, sxyz );

    rgb.x = xyz2rgb( rgb.x );
    rgb.y = xyz2rgb( rgb.y );
    rgb.z = xyz2rgb( rgb.z );

    return rgb::saturate( rgb );
}


////////////////////////////////////////////////////////////////////////////////
col_t fromCIELCh( const col_t& lch ) {
    return rgb::fromCIEXYZ( ciexyz::fromCIELab( cielab::fromCIELCh( lch ) ) );
}


////////////////////////////////////////////////////////////////////////////////
col_t spaceRoundtrip( const col_t& rgb1 )
{
    const col_t xyz1 = ciexyz::fromRGB( rgb1 );
    const col_t lab1 = cielab::fromCIEXYZ( xyz1 );
    const col_t lch1 = cielch::fromCIELab( lab1 );
    const col_t lab2 = cielab::fromCIELCh( lch1 );
    const col_t xyz2 = ciexyz::fromCIELab( lab2 );
    const col_t rgb2 = rgb::fromCIEXYZ( xyz2 );

    std::cout << "rgb1:	" << glm::to_string( rgb1 ) << std::endl;
    std::cout << "xyz1:	" << glm::to_string( xyz1 ) << std::endl;
    std::cout << "lab1:	" << glm::to_string( lab1 ) << std::endl;
    std::cout << "lch1:	" << glm::to_string( lch1 ) << std::endl;
    std::cout << "lab2:	" << glm::to_string( lab2 ) << std::endl;
    std::cout << "xyz2:	" << glm::to_string( xyz2 ) << std::endl;
    std::cout << "rgb2:	" << glm::to_string( rgb2 ) << std::endl;

    return rgb2;
}


////////////////////////////////////////////////////////////////////////////////
col_t typeRoundtrip( const col_t& rgb1 )
{
    const auto rgb8 = rgb8::fromRGB( rgb1 );
    const auto rgb2 = rgb::fromRGB8( rgb8 );

    std::cout << "rgb1: " << glm::to_string( rgb1 ) << std::endl;
    std::cout << "rgb8: " << glm::to_string( rgb8 ) << std::endl;
    std::cout << "rgb2: " << glm::to_string( rgb2 ) << std::endl;

    return rgb2;
}


}   //  ::tq::rgb


namespace rgb8 {


////////////////////////////////////////////////////////////////////////////////
col8_t fromRGB( const col_t& rgb )
{
    col8_t rgb8;
    rgb8.x = rgb.x * 255;
    rgb8.y = rgb.y * 255;
    rgb8.z = rgb.z * 255;

    return rgb8;
}


}   //  ::tq::rgb8


namespace hsv {


////////////////////////////////////////////////////////////////////////////////
//  r: [0, 1], g: [0, 1], b: [0, 1]
//  [2] https://www.cs.rit.edu/~ncs/color/t_convert.html
col_t fromRGB( float r, float g, float b )
{
    const float cmax = glm::max( glm::max( r, g ), b );
    const float cmin = glm::min( glm::min( r, g ), b );
    const float delta = cmax - cmin;

    col_t col;
    col.z = cmax;

    if ( cmax != 0.f ) {
        col.y = delta / cmax;
    } else {
        col.x =-1;
        col.y = 0;
        return col;
    }

    if ( glm::epsilonEqual( r, cmax, glm::epsilon<float>() ) ) {
        col.x = ( g - b ) / delta;		// between yellow & magenta
    } else if ( glm::epsilonEqual( g, cmax, glm::epsilon<float>() ) ) {
        col.x = 2 + ( b - r ) / delta;	// between cyan & yellow
    } else {
        col.x = 4 + ( r - g ) / delta;	// between magenta & cyan
    }

    col.x *= 60;    // degrees

    if ( col.x < 0 ) {
        col.x += 360;
    }

    col.x /= 360.0f;
    return col;
}


////////////////////////////////////////////////////////////////////////////////
col_t fromRGB( const col_t& rgb ) {
    return fromRGB( rgb.x, rgb.y, rgb.z );
}


}   //  ::tq::hsv


namespace cielab {


////////////////////////////////////////////////////////////////////////////////
//  xyz \in [ 0, 1 ]
//  l \in [ 0, 100 ]
//  ab \in [ -128, 128 ]
//  [3] http://docs.opencv.org/3.1.0/de/d25/imgproc_color_conversions.html#gsc.tab=0
//  [4] https://github.com/mbostock/d3/blob/master/src/color/rgb.js
col_t fromCIEXYZ( const col_t& xyz )
{
    auto xyz2lab = []( const float x ) -> float {
        return ( x > 0.008856f ) ?
            std::cbrtf( x ) :
            ( 7.787f * x + 16.f / 116.f );
    };

    col_t sxyz;
    sxyz.x = xyz2lab( xyz.x );
    sxyz.y = xyz2lab( xyz.y );
    sxyz.z = xyz2lab( xyz.z );

    col_t lab;
    lab.x = 116.f * sxyz.y - 16.f;
    lab.y = 500.f * ( sxyz.x - sxyz.y );
    lab.z = 200.f * ( sxyz.y - sxyz.z );

    return lab;
}


////////////////////////////////////////////////////////////////////////////////
col_t fromCIELCh( const col_t& lch)
{
    col_t lab;
    lab.x = lch.x;
    lab.y = std::cosf( lch.z ) * lch.y;
    lab.z = std::sinf( lch.z ) * lch.y;

    return lab;
}


}   //  ::tq::cielab


namespace ciexyz {


////////////////////////////////////////////////////////////////////////////////
col_t fromCIELab( const col_t& lab )
{
    col_t xyz;
    xyz.y = ( lab.x + 16.f ) / 116.f;
    xyz.x = xyz.y + lab.y / 500.0f;
    xyz.z = xyz.y - lab.z / 200.0f;

    auto lab2xyz = []( const float x ) -> float {
        return ( x > 0.206893034f ) ?
            ( x * x * x ) :
            ( ( x - 16.f / 116.f ) / 7.787037f );
    };

    xyz.x = lab2xyz( xyz.x );
    xyz.y = lab2xyz( xyz.y );
    xyz.z = lab2xyz( xyz.z );

    return xyz;
}


////////////////////////////////////////////////////////////////////////////////
//  rgb \in [ 0, 1 ]
//  xyz \in [ 0, 1 ]
col_t fromRGB( const col_t& rgb )
{
    auto rgb2xyz = []( const float x ) -> float {
        return ( x <= 0.04045f ) ?
            ( x / 12.92f ) :
            ( std::powf( ( x + 0.055f ) / 1.055f, 2.4f ) );
    };

    col_t sxyz;
    sxyz.x = rgb2xyz( rgb.x );
    sxyz.y = rgb2xyz( rgb.y );
    sxyz.z = rgb2xyz( rgb.z );

    col_t xyz;
    xyz.x = glm::dot( { 0.4124564f, 0.3575761f, 0.1804375f }, sxyz );
    xyz.y = glm::dot( { 0.2126729f, 0.7151522f, 0.0721750f }, sxyz );
    xyz.z = glm::dot( { 0.0193339f, 0.1191920f, 0.9503041f }, sxyz );

    xyz = xyz / xyz_ref;

    return xyz;
}


}   //  ::tq::ciexyz


namespace cielch {


////////////////////////////////////////////////////////////////////////////////
//  l \in [ 0, 100 ]
col_t fromCIELab( const col_t& lab )
{
    const float h = std::atan2f( lab.z, lab.y );

    col_t lch;
    lch.x = lab.x;
    lch.y = std::sqrtf( lab.y * lab.y + lab.z * lab.z );
    lch.z = h;

    return lch;
}


////////////////////////////////////////////////////////////////////////////////
col_t fromRGB( const col_t& rgb ) {
    return cielch::fromCIELab( cielab::fromCIEXYZ( ciexyz::fromRGB( rgb ) ) );
}


}   //  ::tq::cielch


}   //  ::tq
