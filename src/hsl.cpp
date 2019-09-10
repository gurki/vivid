#include "vivid/conversion.h"
#include "vivid/data/xterm.h"

#include <glm/common.hpp>
#include <glm/gtc/epsilon.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/component_wise.hpp>

namespace vivid::hsl {


////////////////////////////////////////////////////////////////////////////////
hsl_t fromRgb( const rgb_t& rgb )
{
    const auto cmax = glm::compMax( static_cast<col_t>( rgb ) );
    const auto cmin = glm::compMin( static_cast<col_t>( rgb ) );
    const auto delta = cmax - cmin;

    hsl_t hsl = {
        0.f,
        0.f,
        ( cmax + cmin ) / 2.f
    };

    if ( glm::epsilonEqual( delta, 0.f, glm::epsilon<float>() ) ) {
        return hsl;
    }

    if ( glm::epsilonEqual( cmax, rgb.x, glm::epsilon<float>() ) ) {
        hsl.x = std::fmod( ( rgb.y - rgb.z ) / delta, 6.f );
    } else if ( glm::epsilonEqual( cmax, rgb.y, glm::epsilon<float>() ) ) {
        hsl.x = ( rgb.z - rgb.x ) / delta + 2.f;
    } else {
        hsl.x = ( rgb.x - rgb.y ) / delta + 4.f;
    }

    hsl.y = delta / ( 1.f - std::abs( 2.f * hsl.z - 1.f ) );
    hsl.x /= 6.f;
    hsl.x = std::fmod( hsl.x + 1.f, 1.f );

    return hsl;
}


////////////////////////////////////////////////////////////////////////////////
hsl_t fromHsv( const hsv_t& hsv ) {
    return hsl::fromRgb( rgb::fromHsv( hsv ) );
}


////////////////////////////////////////////////////////////////////////////////
hsl_t fromIndex( const uint8_t index ) {
    return hsl::fromRgb( rgb::fromRgb32( data::xterm.at( index ).rgb32 ) );
}


}   //  ::vivid::hsl
