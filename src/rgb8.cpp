#include "vivid/conversion.h"
#include <glm/common.hpp>

namespace tq::rgb888 {


////////////////////////////////////////////////////////////////////////////////
colu8_t fromRGB( const col_t& rgb ) {
    return glm::clamp( 255.f * rgb, 0.f, 255.f );
}


}   //  ::tq::rgb888
