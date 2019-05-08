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

