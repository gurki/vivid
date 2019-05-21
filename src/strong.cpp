#include "vivid/strong.h"
#include "vivid/conversion.h"
#include "vivid/functions.h"

#include <glm/glm.hpp>
#include <glm/common.hpp>
#include <glm/gtc/epsilon.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/component_wise.hpp>

namespace vivid {


////////////////////////////////////////////////////////////////////////////////
rgb_t::rgb_t( const float x, const float y, const float z ) : col_t( x, y, z ) { std::cout << "rgb::xyz \n"; }
rgb_t::rgb_t( const srgb_t& srgb ) : col_t( srgb ) {}
rgb_t::rgb_t( const lrgb_t& lrgb ) : col_t( lrgb ) {}
rgb_t::rgb_t( const col_t& col ) : col_t( col ) { std::cout << "rgb::col \n"; }
rgb_t::rgb_t( const hsl_t& hsl ) : col_t( rgb::fromHsl( hsl ) ) {}


////////////////////////////////////////////////////////////////////////////////
srgb_t::srgb_t( const float x, const float y, const float z ) : col_t( x, y, z ) {}
srgb_t::srgb_t( const col_t& col ) : col_t( col ) {}
srgb_t::srgb_t( const rgb_t& rgb ) : col_t( rgb ) {}
srgb_t::srgb_t( const lrgb_t& lrgb ) : col_t( srgb::fromLinear( lrgb ) ) {}


////////////////////////////////////////////////////////////////////////////////
lrgb_t::lrgb_t( const float x, const float y, const float z ) : col_t( x, y, z ) {}
lrgb_t::lrgb_t( const col_t& col ) : col_t( col ) {}
lrgb_t::lrgb_t( const rgb_t& rgb ) : col_t( rgb ) {}
lrgb_t::lrgb_t( const srgb_t& srgb ) : col_t( srgb::toLinear( srgb ) ) {}


////////////////////////////////////////////////////////////////////////////////
hsl_t::hsl_t( const float x, const float y, const float z ) : col_t( x, y, z ) {}
hsl_t::hsl_t( const col_t& col ) : col_t( col ) {}
hsl_t::hsl_t( const rgb_t& rgb ) : col_t( hsl::fromRgb( rgb ) ) {}


////////////////////////////////////////////////////////////////////////////////
lch_t::lch_t( const float x, const float y, const float z ) : col_t( x, y, z ) {}
lch_t::lch_t( const col_t& col ) : col_t( col ) { std::cout << "lch::col \n"; }
lch_t::lch_t( const rgb_t& rgb ) : col_t( lch::fromRgb( srgb_t( rgb ) ) ) {}
lch_t::lch_t( const lrgb_t& lrgb ) : col_t( lch::fromRgb( srgb_t( lrgb ) ) ) {}
lch_t::lch_t( const srgb_t& srgb ) : col_t( lch::fromRgb( srgb ) ) {}
lch_t::lch_t( const hsl_t& hsl ) : col_t( lch::fromRgb( rgb::fromHsl( hsl ) )) {}


////////////////////////////////////////////////////////////////////////////////
rgb_t lerp( const rgb_t& rgb1, const rgb_t& rgb2, const float t ) {
    return rgb_t( rgb1 + t * ( rgb2 - rgb1 ) );
}


////////////////////////////////////////////////////////////////////////////////
hsl_t lerp( const hsl_t& hsl1, const hsl_t& hsl2, const float t )
{
    hsl_t hsl1a = hsl1;

    if ( std::abs( hsl1a.x - hsl2.x ) > 0.5f )
    {
        if( hsl1a.x > hsl2.x ) {
            hsl1a.x -= 1.0f;
        } else {
            hsl1a.x += 1.0f;
        }
    }

    auto hsl = hsl_t( hsl1a + t * ( hsl2 - hsl1a ) );
    hsl.x = std::fmodf( hsl.x, 1.0f );

    return hsl;
}


////////////////////////////////////////////////////////////////////////////////
lch_t lerp( const lch_t& lch1, const lch_t& lch2, const float t )
{
    col_t delta = lch2 - lch1;

    //  move along shortest path (wrap [0; 360])
    if ( delta.z > 180.f ) {
        delta.z -= 360.f;
    } else if ( delta.z < - 180.f ) {
        delta.z += 380.f;
    }

    auto interp = lch_t( lch1 + t * delta );

    //  project back to [0; 360]
    interp.z = std::fmodf( interp.z + 360.f, 360.f );
    return interp;
}


}
