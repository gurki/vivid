#pragma once

#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/component_wise.hpp>

namespace vivid {


using col_t = glm::vec<3, float>;
using col8_t = glm::vec<3, uint8_t>;


inline bool fuzzyEqual( const col_t& c1, const col_t& c2 ) {
    //  compares to ~1/255th
    return glm::all( glm::lessThan( glm::abs( c1 - c2 ), glm::vec3( 0.004f ) ));
}


inline bool fuzzyHueEqual( const col_t& c1, const col_t& c2 )
{
    //  compares to ~1/255th and wraps hue

    const auto delta = glm::abs( c1 - c2 );

    return (
        ( delta.x < 0.004f || delta.x > 0.096f ) &&
        ( delta.y < 0.004f ) &&
        ( delta.z < 0.004f )
    );
}


}   //  ::vivid
