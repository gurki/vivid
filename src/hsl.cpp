#include "vivid/conversion.h"
#include "vivid/colortable.h"

#include <glm/common.hpp>
#include <glm/gtc/epsilon.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/component_wise.hpp>

namespace tq::hsl {


////////////////////////////////////////////////////////////////////////////////
col_t fromRGB( const col_t& rgb )
{
    const auto cmax = glm::compMax( rgb );
    const auto cmin = glm::compMin( rgb );
    const auto delta = cmax - cmin;

    col_t hsl = {
        0.f,
        0.f,
        ( cmax + cmin ) / 2.f
    };

    if ( glm::epsilonEqual( delta, 0.f, glm::epsilon<float>() ) ) {
        return hsl;
    }

    if ( glm::epsilonEqual( cmax, rgb.x, glm::epsilon<float>() ) ) {
        hsl.x = std::fmodf( ( rgb.y - rgb.z ) / delta, 6.f );
    } else if ( glm::epsilonEqual( cmax, rgb.y, glm::epsilon<float>() ) ) {
        hsl.x = ( rgb.z - rgb.x ) / delta + 2.f;
    } else {
        hsl.x = ( rgb.x - rgb.y ) / delta + 4.f;
    }

    hsl.y = delta / ( 1.f - std::abs( 2.f * hsl.z - 1.f ) );
    hsl.x *= 60;

    if ( hsl.x < 0 ) {
        hsl.x += 360;
    }

    hsl.x /= 360.0f;
    return hsl;
}


////////////////////////////////////////////////////////////////////////////////
col_t fromHSV( const col_t& hsv ) {
    return hsl::fromRGB( rgb::fromHSV( hsv ) );
}


////////////////////////////////////////////////////////////////////////////////
col_t fromIndex( const uint8_t index ) {
    return ColorTable::hsl( index );
}


}   //  ::tq::hsl
