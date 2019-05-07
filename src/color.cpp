#include "vivid/color.h"

#include <glm/glm.hpp>
#include <glm/common.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/string_cast.hpp>

#include <iostream>

namespace tq {

//  observer = 2°, illuminant= D65
//  [1] http://www.easyrgb.com/index.php?X=MATH&H=08#text8
static const glm::vec3 xyz_ref = glm::vec3( 0.95047f, 1.f, 1.08883f );


namespace rgb {


////////////////////////////////////////////////////////////////////////////////
glm::vec3 lerp_hsv(
    const glm::vec3& rgb1,
    const glm::vec3& rgb2,
    const float t )
{
    glm::vec3 hsv1 = to_hsv( rgb1 );
    glm::vec3 hsv2 = to_hsv( rgb2 );

    glm::vec3 hsv;

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

    return from_hsv( hsv );
}


////////////////////////////////////////////////////////////////////////////////
glm::vec3 lerp_cielch(
    const glm::vec3& rgb1,
    const glm::vec3& rgb2,
    const float t )
{
    //  FIXME: make sure interpolation yields valid colors
    glm::vec3 lch1 = cielab_to_cielch( ciexyz_to_cielab( to_ciexyz( rgb1 ) ) );
    glm::vec3 lch2 = cielab_to_cielch( ciexyz_to_cielab( to_ciexyz( rgb2 ) ) );

    glm::vec3 delta = lch2 - lch1;

    if ( delta.z > glm::pi<float>() ) {
        delta.z -= glm::two_pi<float>();
    } else if ( delta.z < - glm::pi<float>() ) {
        delta.z += glm::two_pi<float>();
    }

    glm::vec3 lch = lch1 + t * delta;

    return from_ciexyz( cielab_to_ciexyz( cielch_to_cielab( lch ) ) );
}


////////////////////////////////////////////////////////////////////////////////
// input 0..255 for rainbow colors!
glm::vec3 rainbow( const int c )
{
    const int k = c % 255;
    glm::vec3 col;

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
glm::vec3 saturate( const glm::vec3& rgb )
{
    auto res = rgb;

    res.x = glm::clamp( rgb.x, 0.f, 1.f );
    res.y = glm::clamp( rgb.y, 0.f, 1.f );
    res.z = glm::clamp( rgb.z, 0.f, 1.f );

    return res;
}


////////////////////////////////////////////////////////////////////////////////
//  h: [0, 1], s: [0, 1], v: [0, 1]
glm::vec3 from_hsv( float h, float s, float v )
{
    h = ( h > 0.f ) ? ( std::fmodf( h, 1.f ) ) : ( 1.f + std::fmodf( h, 1.f ) );   //  wrap
    s = glm::clamp( s, 0.f, 1.f );
    v = glm::clamp( v, 0.f, 1.f );

    glm::vec3 col;

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
            case 0:  col = glm::vec3( c, x, 0.f ); break;
            case 1:  col = glm::vec3( x, c, 0.f ); break;
            case 2:  col = glm::vec3( 0.f, c, x ); break;
            case 3:  col = glm::vec3( 0.f, x, c ); break;
            case 4:  col = glm::vec3( x, 0.f, c ); break;
            default: col = glm::vec3( c, 0.f, x ); break;
        }

        const float m = v - c;
        col[ 0 ] += m;
        col[ 1 ] += m;
        col[ 2 ] += m;
    }

    return col;
}


////////////////////////////////////////////////////////////////////////////////
//  r: [0, 1], g: [0, 1], b: [0, 1]
//  [1] https://www.cs.rit.edu/~ncs/color/t_convert.html
glm::vec3 to_hsv( float r, float g, float b )
{
    const float cmax = glm::max( glm::max( r, g ), b );
    const float cmin = glm::min( glm::min( r, g ), b );
    const float delta = cmax - cmin;

    glm::vec3 col;
    col.z = cmax;

    if ( cmax != 0.f ) {
        col.y = delta / cmax;
    } else {
        col.x =-1;
        col.y = 0;
        return col;
    }

    if ( r == cmax ) {
        col.x = ( g - b ) / delta;		// between yellow & magenta
    } else if ( g == cmax ) {
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
glm::vec3 from_hsv( const glm::vec3& hsv ) {
    return from_hsv( hsv.x, hsv.y, hsv.z );
}


////////////////////////////////////////////////////////////////////////////////
glm::vec3 from_ciexyz( const glm::vec3& xyz )
{
    auto xyz2rgb = []( const float x ) -> float {
        return ( x <= 0.00304f ) ?
            ( 12.92f * x ) :
            ( 1.055f * std::pow( x, 1.f / 2.4f ) - 0.055f );
    };

    const glm::vec3 sxyz = xyz * xyz_ref;

    glm::vec3 rgb = {};
    rgb.x = glm::dot( { 3.2404542f,-1.5371385f,-0.4985134f }, sxyz );
    rgb.y = glm::dot( {-0.9692600f, 1.8760108f, 0.0415560f }, sxyz );
    rgb.z = glm::dot( { 0.0556434f,-0.2040259f, 1.0572252f }, sxyz );

    rgb.x = xyz2rgb( rgb.x );
    rgb.y = xyz2rgb( rgb.y );
    rgb.z = xyz2rgb( rgb.z );

    return saturate( rgb );
}


////////////////////////////////////////////////////////////////////////////////
glm::vec3 from_cielch( const glm::vec3& lch ) {
    return from_ciexyz( cielab_to_ciexyz( cielch_to_cielab( lch ) ) );
}


////////////////////////////////////////////////////////////////////////////////
glm::vec3 to_hsv( const glm::vec3& rgb ) {
    return to_hsv( rgb.x, rgb.y, rgb.z );
}


////////////////////////////////////////////////////////////////////////////////
//  rgb \in [ 0, 1 ]
//  xyz \in [ 0, 1 ]
glm::vec3 to_ciexyz( const glm::vec3& rgb )
{
    auto rgb2xyz = []( const float x ) -> float {
        return ( x <= 0.04045f ) ?
            ( x / 12.92f ) :
            ( std::powf( ( x + 0.055f ) / 1.055f, 2.4f ) );
    };

    glm::vec3 sxyz;
    sxyz.x = rgb2xyz( rgb.x );
    sxyz.y = rgb2xyz( rgb.y );
    sxyz.z = rgb2xyz( rgb.z );

    glm::vec3 xyz;
    xyz.x = glm::dot( { 0.4124564f, 0.3575761f, 0.1804375f }, sxyz );
    xyz.y = glm::dot( { 0.2126729f, 0.7151522f, 0.0721750f }, sxyz );
    xyz.z = glm::dot( { 0.0193339f, 0.1191920f, 0.9503041f }, sxyz );

    xyz = xyz / xyz_ref;

    return xyz;
}


////////////////////////////////////////////////////////////////////////////////
glm::vec3 to_cielch( const glm::vec3& rgb ) {
    return cielab_to_cielch( ciexyz_to_cielab( to_ciexyz( rgb ) ) );
}


}   //  ::tq::rgb



////////////////////////////////////////////////////////////////////////////////
//  xyz \in [ 0, 1 ]
//  l \in [ 0, 100 ]
//  ab \in [ -128, 128 ]
//  [1] http://docs.opencv.org/3.1.0/de/d25/imgproc_color_conversions.html#gsc.tab=0
//  [2] https://github.com/mbostock/d3/blob/master/src/color/rgb.js
glm::vec3 ciexyz_to_cielab( const glm::vec3& xyz )
{
    auto xyz2lab = []( const float x ) -> float {
        return ( x > 0.008856f ) ?
            std::cbrtf( x ) :
            ( 7.787f * x + 16.f / 116.f );
    };

    glm::vec3 sxyz;
    sxyz.x = xyz2lab( xyz.x );
    sxyz.y = xyz2lab( xyz.y );
    sxyz.z = xyz2lab( xyz.z );

    glm::vec3 lab;
    lab.x = 116.f * sxyz.y - 16.f;
    lab.y = 500.f * ( sxyz.x - sxyz.y );
    lab.z = 200.f * ( sxyz.y - sxyz.z );

    return lab;
}


////////////////////////////////////////////////////////////////////////////////
glm::vec3 cielab_to_ciexyz( const glm::vec3& lab )
{
    glm::vec3 xyz;
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
//  l \in [ 0, 100 ]
glm::vec3 cielab_to_cielch( const glm::vec3& lab )
{
    const float h = std::atan2f( lab.z, lab.y );

    glm::vec3 lch;
    lch.x = lab.x;
    lch.y = std::sqrtf( lab.y * lab.y + lab.z * lab.z );
    lch.z = h;

    return lch;
}


////////////////////////////////////////////////////////////////////////////////
glm::vec3 cielch_to_cielab( const glm::vec3& lch)
{
    glm::vec3 lab;
    lab.x = lch.x;
    lab.y = std::cosf( lch.z ) * lch.y;
    lab.z = std::sinf( lch.z ) * lch.y;

    return lab;
}


////////////////////////////////////////////////////////////////////////////////
void log_rgb_to_cielch( const glm::vec3& rgb1 )
{
    const glm::vec3 xyz1 = rgb::to_ciexyz( rgb1 );
    const glm::vec3 lab1 = ciexyz_to_cielab( xyz1 );
    const glm::vec3 lch1 = cielab_to_cielch( lab1 );
    const glm::vec3 lab2 = cielch_to_cielab( lch1 );
    const glm::vec3 xyz2 = cielab_to_ciexyz( lab2 );
    const glm::vec3 rgb2 = rgb::from_ciexyz( xyz2 );

    std::cout << "rgb1:	" << glm::to_string( rgb1 ) << std::endl;
    std::cout << "xyz1:	" << glm::to_string( xyz1 ) << std::endl;
    std::cout << "lab1:	" << glm::to_string( lab1 ) << std::endl;
    std::cout << "lch1:	" << glm::to_string( lch1 ) << std::endl;
    std::cout << "lab2:	" << glm::to_string( lab2 ) << std::endl;
    std::cout << "xyz2:	" << glm::to_string( xyz2 ) << std::endl;
    std::cout << "rgb2:	" << glm::to_string( rgb2 ) << std::endl;
}


}   //  ::tq
