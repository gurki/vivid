#include "vivid/conversion.h"

#include <glm/glm.hpp>
#include <glm/gtc/epsilon.hpp>
#include <glm/gtc/constants.hpp>

namespace tq::hsv {


////////////////////////////////////////////////////////////////////////////////
//  r: [0, 1], g: [0, 1], b: [0, 1]
//  [2] https://www.cs.rit.edu/~ncs/color/t_convert.html
col_t fromRGB( float r, float g, float b )
{
    const float cmax = glm::max( glm::max( r, g ), b );
    const float cmin = glm::min( glm::min( r, g ), b );
    const float delta = cmax - cmin;

    col_t hsv = { 0.f, 0.f, cmax };

    if ( cmax != 0.f ) {
        hsv.y = delta / cmax;
    } else {
        hsv.x =-1;
        hsv.y = 0;
        return hsv;
    }

    if ( glm::epsilonEqual( r, cmax, glm::epsilon<float>() ) ) {
        hsv.x = ( g - b ) / delta;		// between yellow & magenta
    } else if ( glm::epsilonEqual( g, cmax, glm::epsilon<float>() ) ) {
        hsv.x = 2 + ( b - r ) / delta;	// between cyan & yellow
    } else {
        hsv.x = 4 + ( r - g ) / delta;	// between magenta & cyan
    }

    hsv.x *= 60;    // degrees

    if ( hsv.x < 0 ) {
        hsv.x += 360;
    }

    hsv.x /= 360.0f;
    return hsv;
}


////////////////////////////////////////////////////////////////////////////////
col_t fromRGB( const col_t& rgb ) {
    return fromRGB( rgb.x, rgb.y, rgb.z );
}


////////////////////////////////////////////////////////////////////////////////
col_t fromHSL( const col_t& hsl ) {
    return hsv::fromRGB( rgb::fromHSL( hsl ) );
}


}   //  ::tq::hsv

