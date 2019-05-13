#include "vivid/conversion.h"
#include "vivid/colortable.h"
#include "vivid/functions.h"

#include <glm/glm.hpp>
#include <glm/common.hpp>           //  clamp
#include <glm/gtc/constants.hpp>    //  pi
#include <glm/gtx/string_cast.hpp>

#include <iostream>

namespace tq::rgb {


////////////////////////////////////////////////////////////////////////////////
col_t fromRGB888( const colu8_t& rgb888 )
{
    col_t rgb;
    rgb.x = rgb888.x / 255.f;
    rgb.y = rgb888.y / 255.f;
    rgb.z = rgb888.z / 255.f;

    return rgb;
}


////////////////////////////////////////////////////////////////////////////////
col_t fromRGBu32( const uint32_t rgbu32 )
{
    const uint8_t r = ( rgbu32 >> 16 ) & 0xff;
    const uint8_t g = ( rgbu32 >> 8 ) & 0xff;
    const uint8_t b = rgbu32 & 0xff;

    return fromRGB888( { r, g, b } );
}


////////////////////////////////////////////////////////////////////////////////
col_t fromHSV( float h, float s, float v )
{
    h = ( h > 0.f ) ? ( std::fmodf( h, 1.f ) ) : ( 1.f + std::fmodf( h, 1.f ) );   //  wrap
    s = glm::clamp( s, 0.f, 1.f );
    v = glm::clamp( v, 0.f, 1.f );

    if( s == 0.f ) {
        return { v, v, v };
    }

    col_t rgb = {};

    const float k = h * 6.f;
    const int d = int( std::floorf( k ) );
    const float C = v * s;
    const float X = C * ( 1.f - std::fabsf( std::fmodf( k, 2.f ) - 1.f ) );
    const float m = v - C;

    switch( d )
    {
        case 0: rgb = col_t( C, X, 0.f ); break;
        case 1: rgb = col_t( X, C, 0.f ); break;
        case 2: rgb = col_t( 0.f, C, X ); break;
        case 3: rgb = col_t( 0.f, X, C ); break;
        case 4: rgb = col_t( X, 0.f, C ); break;
        default: rgb = col_t( C, 0.f, X ); break;
    }

    rgb += m;
    return rgb;
}


////////////////////////////////////////////////////////////////////////////////
col_t fromHSV( const col_t& hsv ) {
    return rgb::fromHSV( hsv.x, hsv.y, hsv.z );
}


////////////////////////////////////////////////////////////////////////////////
//  [1] https://www.rapidtables.com/convert/color/hsl-to-rgb.html
col_t fromHSL( const col_t& hsl )
{
    const float k = hsl.x * 6.f;
    const float C = ( 1.f - std::abs( 2.f * hsl.z - 1.f ) ) * hsl.y;
    const float X = C * ( 1.f - std::abs( std::fmodf( k, 2.f ) - 1.f ) );
    const float m = hsl.z - C / 2.f;
    const int d = int( std::floorf( k ) );

    col_t rgb = {};

    switch( d )
    {
        case 0: rgb = col_t( C, X, 0.f ); break;
        case 1: rgb = col_t( X, C, 0.f ); break;
        case 2: rgb = col_t( 0.f, C, X ); break;
        case 3: rgb = col_t( 0.f, X, C ); break;
        case 4: rgb = col_t( X, 0.f, C ); break;
        default: rgb = col_t( C, 0.f, X ); break;
    }

    rgb += m;
    return rgb;
}


////////////////////////////////////////////////////////////////////////////////
col_t fromCIEXYZ( const col_t& xyz )
{
    auto xyz2rgb = []( const float x ) -> float {
        return ( x <= 0.00304f ) ?
            ( 12.92f * x ) :
            ( 1.055f * std::pow( x, 1.f / 2.4f ) - 0.055f );
    };

    const col_t sxyz = xyz * ciexyz::xyz_ref;

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
col_t fromHex( const std::string& hexStr ) {
    return rgb::fromRGBu32( rgbu32::fromHex( hexStr ) );
}


////////////////////////////////////////////////////////////////////////////////
col_t fromIndex( const uint8_t code ) {
    return rgb::fromRGB888( ColorTable::rgb888( code ) );
}



}   //  ::tq::rgb
