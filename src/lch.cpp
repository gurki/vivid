#include "vivid/conversion.h"
#include <glm/gtc/constants.hpp>
#include <cmath>

namespace vivid::lch {


////////////////////////////////////////////////////////////////////////////////
col_t fromLab( const col_t& lab )
{
    const float h = glm::degrees( std::atan2f( lab.z, lab.y ) );

    col_t lch;
    lch.x = lab.x;
    lch.y = std::sqrtf( lab.y * lab.y + lab.z * lab.z );
    lch.z = ( h >= 0 ) ? h : ( h + 360.f );

    return lch;
}


////////////////////////////////////////////////////////////////////////////////
col_t fromRgb( const col_t& rgb ) {
    return lch::fromLab( lab::fromXyz( xyz::fromRgb( rgb ) ) );
}


////////////////////////////////////////////////////////////////////////////////
col_t fromXyz( const col_t& xyz ) {
    return lch::fromLab( lab::fromXyz( xyz ) );
}


}   //  ::vivid::cielch
