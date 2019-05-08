#include "vivid/conversion.h"

namespace tq::cielch {


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
