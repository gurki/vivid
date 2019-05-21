#include "vivid/conversion.h"
#include "vivid/functions.h"

namespace vivid::adobe {


////////////////////////////////////////////////////////////////////////////////
adobe_t fromRgb( const rgb_t& rgb ) {
    return adobe::fromXyz( xyz::fromRgb( rgb ) );
}


////////////////////////////////////////////////////////////////////////////////
adobe_t fromXyz( const xyz_t& xyz )
{
    const auto lrgb = static_cast<lrgb_t>( xyz * matrices::xyz_to_adobe );

    return static_cast<adobe_t>(
        rgb::invGamma( lrgb, adobe::gamma )
    );
}


}   //  ::vivid::adobe
