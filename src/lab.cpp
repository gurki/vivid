#include "vivid/conversion.h"
#include "vivid/profiles.h"
#include <glm/glm.hpp>
#include <cmath>

namespace vivid::lab {


////////////////////////////////////////////////////////////////////////////////
lab_t fromXyz( const xyz_t& xyz )
{
    static const float eps = 0.008856f;

    auto xyz2lab = []( const float x ) -> float {
        return ( x > eps ) ?
            std::cbrtf( x ) :
            ( 7.78448275862069f * x + 0.137931034482759f ); //  ( kappa * x + 16 ) / 116
    };

    const auto xyzr = xyz / profiles::tri_d65;

    xyz_t fxyz;
    fxyz.x = xyz2lab( xyzr.x );
    fxyz.y = xyz2lab( xyzr.y );
    fxyz.z = xyz2lab( xyzr.z );

    lab_t lab;
    lab.x = 116.f * fxyz.y - 16.f;
    lab.y = 500.f * ( fxyz.x - fxyz.y );
    lab.z = 200.f * ( fxyz.y - fxyz.z );

    return lab;
}


////////////////////////////////////////////////////////////////////////////////
lab_t fromLch( const lch_t& lch )
{
    lab_t lab;
    lab.x = lch.x;
    lab.y = lch.y * std::cos( glm::radians( lch.z ) );
    lab.z = lch.y * std::sin( glm::radians( lch.z ) );

    return lab;
}


}   //  ::vivid::cielab
