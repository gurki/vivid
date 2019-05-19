#include "vivid/conversion.h"
#include "vivid/stream.h"
#include "vivid/colortable.h"

#include "utility.h"
#include "catch.hpp"


////////////////////////////////////////////////////////////////////////////////
TEST_CASE( "Manual Conversions", "[conversions]" )
{
    using namespace vivid;
    ColorTable::load( VIVID_ROOT_PATH "res/colors.json" );

    col_t rgb1 = { 1.f, 0.f, 0.f };
    auto xyz1 = xyz::fromRgb( rgb1 );
    auto lab1 = lab::fromXyz( xyz1 );

    col_t xyz2 = { 0.412456, 0.212673, 0.019334 };
    col_t lab2 = { 53.2408, 80.0925, 67.2032 };

    CAPTURE( rgb1, xyz1, xyz2, lab1, lab2 );
    REQUIRE( fuzzyEqual( xyz1, xyz2 ) );
    REQUIRE( fuzzyEqual( lab1, lab2 ) );
}
