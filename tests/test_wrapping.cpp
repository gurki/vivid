#include "utility.h"

#include "vivid/interpolation.h"
#include "vivid/conversion.h"
#include "vivid/stream.h"

#include "catch.hpp"


////////////////////////////////////////////////////////////////////////////////
TEST_CASE( "Wrapping", "[interpolation]" )
{
    using namespace vivid;

    SECTION( "LCH" ) 
    {
        const lch_t colA { 10.f, 0.f, 10.f };
        const lch_t colB { 40.f, 20.f, 200.f };

        const lch_t colAB = lerp( colA, colB, 0.5f );
        const lch_t colBA = lerp( colB, colA, 0.5f );

        CAPTURE( colA, colB, colAB, colBA );
        REQUIRE( colAB == colBA );
    }
}