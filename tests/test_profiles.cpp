#include "utility.h"
#include "vivid/vivid.h"
#include "vivid/profiles.h"
#include "vivid/fuzzy.h"

#include "catch.hpp"
#include <glm/gtc/epsilon.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/component_wise.hpp>


////////////////////////////////////////////////////////////////////////////////
TEST_CASE( "Profiles", "[profiles]" )
{
    using namespace vivid;

    SECTION( "Chromaticity D65/2°" )
    {
        const glm::vec2 xy1a = { 0.31271f, 0.32902f };
        const glm::vec3 XYZ1a = { 0.95047f, 1.f, 1.08883f };

        const auto XYZ1b = tristimulus( xy1a.x, xy1a.y );
        const auto xy1b = chromaticity( XYZ1a.x, XYZ1a.y, XYZ1a.z );

        CAPTURE( XYZ1a, XYZ1b, xy1a, xy1b );
        REQUIRE( fuzzyEqual( XYZ1a, XYZ1b, 0.0001f ) );
        REQUIRE( fuzzyEqual( xy1a, xy1b, 0.0001f ) );
    }


    SECTION( "Chromaticity D65/10°" )
    {
        const glm::vec2 xy1a = { 0.31382, 0.33100f };
        const glm::vec3 XYZ1a = { 0.948110f, 1.f, 1.07304f };

        const auto XYZ1b = tristimulus( xy1a.x, xy1a.y );
        const auto xy1b = chromaticity( XYZ1a.x, XYZ1a.y, XYZ1a.z );

        CAPTURE( XYZ1a, XYZ1b, xy1a, xy1b );
        REQUIRE( fuzzyEqual( XYZ1a, XYZ1b, 0.0001f ) );
        REQUIRE( fuzzyEqual( xy1a, xy1b, 0.0001f ) );
    }


    SECTION( "Working Space Matrices" )
    {
        //  sRGB
        {
            const glm::vec3 rgbx = { 0.64f, 0.30f, 0.15f };
            const glm::vec3 rgby = { 0.33f, 0.60f, 0.06f };
            const glm::mat3 M = workingSpaceMatrix( profiles::xy_d65, rgbx, rgby );
            const glm::mat3& Mp = matrices::rgb_to_xyz;

            CAPTURE( M, Mp );
            REQUIRE( fuzzyEqual( M, Mp ) );
        }

        //  FIXME(tgurdan): inaccurate for some reason
//        //  adobe (1998)
//        {
//            const glm::vec3 rgbx = { 0.64f, 0.21f, 0.15f };
//            const glm::vec3 rgby = { 0.33f, 0.70f, 0.06f };
//            const glm::mat3 M = workingSpaceMatrix( profiles::xy_d65, rgbx, rgby );
//            const glm::mat3& Mp = matrices::adobe_to_xyz;

//            CAPTURE( M, Mp );
//            REQUIRE( fuzzyEqual( M, Mp ) );
//        }
    }
}
