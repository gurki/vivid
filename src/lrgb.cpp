#include "vivid/conversion.h"
#include "vivid/utility.h"

namespace vivid::lrgb {


////////////////////////////////////////////////////////////////////////////////
lrgb_t fromSrgb( const srgb_t& srgb )
{
    return {
        srgb::inverseCompound( srgb.x ),
        srgb::inverseCompound( srgb.y ),
        srgb::inverseCompound( srgb.z )
    };
}


////////////////////////////////////////////////////////////////////////////////
lrgb_t fromOklab( const oklab_t& oklab )
{
    const float l_ = oklab.x + 0.3963377774f * oklab.y + 0.2158037573f * oklab.z;
    const float m_ = oklab.x - 0.1055613458f * oklab.y - 0.0638541728f * oklab.z;
    const float s_ = oklab.x - 0.0894841775f * oklab.y - 1.2914855480f * oklab.z;

    const float l = l_ * l_ * l_;
    const float m = m_ * m_ * m_;
    const float s = s_ * s_ * s_;

    return {
		+4.0767416621f * l - 3.3077115913f * m + 0.2309699292f * s,
		-1.2684380046f * l + 2.6097574011f * m - 0.3413193965f * s,
		-0.0041960863f * l - 0.7034186147f * m + 1.7076147010f * s,
    };
}


}   //  ::vivid::lrgb
