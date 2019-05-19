#include "vivid/conversion.h"
#include "vivid/colortable.h"
#include "vivid/functions.h"

#include <glm/glm.hpp>
#include <glm/common.hpp>           //  clamp
#include <glm/gtc/constants.hpp>    //  pi
#include <glm/gtx/string_cast.hpp>

#include <iostream>

namespace vivid::rgb {


////////////////////////////////////////////////////////////////////////////////
col_t fromRgb8( const col8_t& rgb8 )
{
    col_t rgb;
    rgb.x = rgb8.x / 255.f;
    rgb.y = rgb8.y / 255.f;
    rgb.z = rgb8.z / 255.f;

    return rgb;
}


////////////////////////////////////////////////////////////////////////////////
col_t fromRgb32( const uint32_t rgb32 ) {
    return rgb::fromRgb8( rgb8::fromRgb32( rgb32 ) );
}


////////////////////////////////////////////////////////////////////////////////
col_t fromHsv( const col_t& hsv )
{
    float h = ( hsv.x > 0.f ) ? ( std::fmodf( hsv.x, 1.f ) ) : ( 1.f + std::fmodf( hsv.x, 1.f ) );   //  wrap
    float s = glm::clamp( hsv.y, 0.f, 1.f );
    float v = glm::clamp( hsv.z, 0.f, 1.f );

    if(  s == 0.f ) {
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
col_t fromHsl( const col_t& hsl )
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
col_t fromXyz( const col_t& xyz ) {
    const col_t lrgb = xyz * matrices::xyz_to_rgb;
    return rgb::saturate( srgb::fromLinear( lrgb ) );
}


////////////////////////////////////////////////////////////////////////////////
col_t fromLch( const col_t& lch ) {
    return rgb::fromXyz( xyz::fromLab( lab::fromLch( lch ) ) );
}


////////////////////////////////////////////////////////////////////////////////
col_t fromHex( const std::string& hexStr ) {
    return rgb::fromRgb32( rgb32::fromHex( hexStr ) );
}


////////////////////////////////////////////////////////////////////////////////
col_t fromIndex( const uint8_t code ) {
    return rgb::fromRgb8( ColorTable::rgb8( code ) );
}


////////////////////////////////////////////////////////////////////////////////
col_t fromName( const std::string& name ) {
    return rgb::fromIndex( index::fromName( name ) );
}


////////////////////////////////////////////////////////////////////////////////
col_t fromAdobe( const col_t& adobe ) {
    return rgb::fromXyz( xyz::fromAdobe( adobe ) );
}


}   //  ::vivid::rgb
