#include "vivid/conversion.h"
#include "vivid/utility.h"
#include "vivid/profiles.h"

namespace vivid::xyz {


////////////////////////////////////////////////////////////////////////////////
xyz_t fromLab( const lab_t& lab )
{
    xyz_t xyz;
    xyz.y = ( lab.x + 16.f ) / 116.f;
    xyz.x = xyz.y + lab.y / 500.0f;
    xyz.z = xyz.y - lab.z / 200.0f;

    static const float cbrt_eps = 0.206893034422964f;

    auto lab2xyz = []( const float x ) -> float {
        return ( x > cbrt_eps ) ?
            ( x * x * x ) :
            ( 0.12841802280527f * x - 0.017712830731761f ); //  ( 116 * x - 16 ) / kappa
    };

    xyz.x = lab2xyz( xyz.x );
    xyz.y = lab2xyz( xyz.y );
    xyz.z = lab2xyz( xyz.z );

    return static_cast<xyz_t>( xyz * profiles::tri_d65 );
}


////////////////////////////////////////////////////////////////////////////////
xyz_t fromSrgb( const srgb_t& srgb ) {
    return static_cast<xyz_t>(
        matrices::rgb_to_xyz * lrgb::fromSrgb( srgb )
    );
}


////////////////////////////////////////////////////////////////////////////////
xyz_t fromLch( const lch_t& lch ) {
    return xyz::fromLab( lab::fromLch( lch ) );
}


////////////////////////////////////////////////////////////////////////////////
xyz_t fromAdobe( const adobe_t& adobe ) {
    return static_cast<xyz_t>(
        matrices::adobe_to_xyz * rgb::gamma( adobe, 1.f / profiles::gamma_adobe )
    );
}



}   //  ::vivid::xyz
