#include "vivid/conversion.h"
#include "vivid/functions.h"

namespace vivid::adobe {


////////////////////////////////////////////////////////////////////////////////
col_t fromRgb( const col_t& rgb ) {
    return adobe::fromXyz( xyz::fromRgb( rgb ) );
}


////////////////////////////////////////////////////////////////////////////////
col_t fromXyz( const col_t& xyz ) {
    col_t lrgb = xyz * matrices::xyz_to_adobe;
    return rgb::gamma( lrgb, 1.f / adobe::gamma );
}


}   //  ::vivid::adobe
