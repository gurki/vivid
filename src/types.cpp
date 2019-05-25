#include "vivid/types.h"
#include "vivid/fuzzy.h"

namespace vivid {


////////////////////////////////////////////////////////////////////////////////
rgb_t::rgb_t( const srgb_t& srgb ) : col_t( srgb ) {}
rgb_t::rgb_t( const lrgb_t& lrgb ) : col_t( lrgb ) {}
rgb_t::rgb_t( const adobe_t& adobe ) : col_t( adobe ) {}


////////////////////////////////////////////////////////////////////////////////
bool fuzzyEqual( const col_t& c1, const col_t& c2 ) {
    //  compares to ~1/255th
    return fuzzyEqual( c1, c2, 0.004f );
}


////////////////////////////////////////////////////////////////////////////////
bool fuzzyHueEqual( const col_t& c1, const col_t& c2 )
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
