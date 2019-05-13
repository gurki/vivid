#include "vivid/conversion.h"
#include "vivid/colortable.h"
#include <glm/common.hpp>

namespace tq::rgb888 {


////////////////////////////////////////////////////////////////////////////////
colu8_t fromRGB( const col_t& rgb ) {
    return glm::clamp( 255.f * rgb, 0.f, 255.f );
}


////////////////////////////////////////////////////////////////////////////////
colu8_t fromIndex( const uint8_t index ) {
    return ColorTable::rgb888( index );
}


}   //  ::tq::rgb888
