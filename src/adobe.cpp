#include "vivid/conversion.h"

namespace vivid::adobe {


////////////////////////////////////////////////////////////////////////////////
col_t fromRgb( const col_t& rgb ) {
    return adobe::fromXyz( xyz::fromRgb( rgb ) );
}


////////////////////////////////////////////////////////////////////////////////
col_t fromXyz( const col_t& xyz ) {
    col_t lrgb = matrices::xyz_to_adobe * xyz;
    return glm::pow( lrgb, glm::vec3( 1.f / adobe::gamma ) );
}


}   //  ::vivid::adobe
