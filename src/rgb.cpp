#include "vivid/conversion.h"
#include "vivid/utility.h"
#include "vivid/data/xterm.h"

#include <glm/glm.hpp>
#include <glm/common.hpp>           //  clamp
#include <glm/gtc/constants.hpp>    //  pi
#include <glm/gtx/string_cast.hpp>

#include <cmath>
#include <iostream>

namespace vivid::rgb {


////////////////////////////////////////////////////////////////////////////////
rgb_t fromRgb8( const col8_t& rgb8 )
{
    rgb_t rgb;
    rgb.x = rgb8.x / 255.f;
    rgb.y = rgb8.y / 255.f;
    rgb.z = rgb8.z / 255.f;

    return rgb;
}


////////////////////////////////////////////////////////////////////////////////
rgb_t fromRgb32( const uint32_t rgb32 ) {
    return rgb::fromRgb8( rgb8::fromRgb32( rgb32 ) );
}


////////////////////////////////////////////////////////////////////////////////
rgb_t fromHsv( const hsv_t& hsv )
{
    float h = ( hsv.x > 0.f ) ? ( std::fmod( hsv.x, 1.f ) ) : ( 1.f + std::fmod( hsv.x, 1.f ) );   //  wrap
    float s = glm::clamp( hsv.y, 0.f, 1.f );
    float v = glm::clamp( hsv.z, 0.f, 1.f );

    if(  s == 0.f ) {
        return { v, v, v };
    }

    rgb_t rgb = {};

    const float k = h * 6.f;
    const int d = int( std::floor( k ) );
    const float C = v * s;
    const float X = C * ( 1.f - std::abs( std::fmod( k, 2.f ) - 1.f ) );
    const float m = v - C;

    switch( d )
    {
        case 0: rgb = { C, X, 0.f }; break;
        case 1: rgb = { X, C, 0.f }; break;
        case 2: rgb = { 0.f, C, X }; break;
        case 3: rgb = { 0.f, X, C }; break;
        case 4: rgb = { X, 0.f, C }; break;
        default: rgb = { C, 0.f, X }; break;
    }

    rgb += m;
    return rgb;
}


////////////////////////////////////////////////////////////////////////////////
rgb_t fromHsl( const hsl_t& hsl )
{
    const float k = hsl.x * 6.f;
    const float C = ( 1.f - std::abs( 2.f * hsl.z - 1.f ) ) * hsl.y;
    const float X = C * ( 1.f - std::abs( std::fmod( k, 2.f ) - 1.f ) );
    const float m = hsl.z - C / 2.f;
    const int d = int( std::floor( k ) );

    rgb_t rgb = {};

    switch( d )
    {
        case 0: rgb = { C, X, 0.f }; break;
        case 1: rgb = { X, C, 0.f }; break;
        case 2: rgb = { 0.f, C, X }; break;
        case 3: rgb = { 0.f, X, C }; break;
        case 4: rgb = { X, 0.f, C }; break;
        default: rgb = { C, 0.f, X }; break;
    }

    rgb += m;
    return rgb;
}


////////////////////////////////////////////////////////////////////////////////
rgb_t fromHex( const std::string& hexStr ) {
    return rgb::fromRgb32( rgb32::fromHex( hexStr ) );
}


}   //  ::vivid::rgb
