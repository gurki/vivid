#include "vivid/conversion.h"
#include "vivid/functions.h"
#include "vivid/data.h"

namespace vivid::srgb {


////////////////////////////////////////////////////////////////////////////////
srgb_t fromLrgb( const lrgb_t& lrgb )
{
    return {
        srgb::compound( lrgb.x ),
        srgb::compound( lrgb.y ),
        srgb::compound( lrgb.z )
    };
}


////////////////////////////////////////////////////////////////////////////////
srgb_t fromXyz( const xyz_t& xyz ) {
    const auto lrgb = static_cast<lrgb_t>( xyz * matrices::xyz_to_rgb );
    return rgb::saturate( srgb::fromLinear( lrgb ) );
}


////////////////////////////////////////////////////////////////////////////////
srgb_t fromLch( const lch_t& lch ) {
    return srgb::fromXyz( xyz::fromLab( lab::fromLch( lch ) ) );
}


////////////////////////////////////////////////////////////////////////////////
srgb_t fromAdobe( const adobe_t& adobe ) {
    return srgb::fromXyz( xyz::fromAdobe( adobe ) );
}


////////////////////////////////////////////////////////////////////////////////
srgb_t fromIndex( const uint8_t index ) {
    return rgb::fromRgb32( data::xterm.at( index ).rgb32 );
}


////////////////////////////////////////////////////////////////////////////////
srgb_t fromName( const std::string& name ) {
    return srgb::fromIndex( index::fromName( name ).value_or( 0 ) );
}



}   //  ::vivid::srgb