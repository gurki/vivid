#include "vivid/conversion.h"
#include <cmath>

namespace vivid::hcl {


////////////////////////////////////////////////////////////////////////////////
//  l \in [ 0, 100 ]
col_t fromLab( const col_t& lab )
{
    const float h = std::atan2f( lab.z, lab.y );

    col_t hcl;
    hcl.x = h;
    hcl.y = std::sqrtf( lab.y * lab.y + lab.z * lab.z );
    hcl.z = lab.x;

    return hcl;
}


////////////////////////////////////////////////////////////////////////////////
col_t fromRgb( const col_t& rgb ) {
    return hcl::fromLab( lab::fromXyz( xyz::fromRgb( rgb ) ) );
}


}   //  ::vivid::cielch
