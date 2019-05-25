#include "vivid/conversion.h"
#include "vivid/utility.h"

namespace vivid::lrgb {


lrgb_t fromSrgb( const srgb_t& srgb )
{
    return {
        srgb::inverseCompound( srgb.x ),
        srgb::inverseCompound( srgb.y ),
        srgb::inverseCompound( srgb.z )
    };
}


}   //  ::vivid::lrgb
