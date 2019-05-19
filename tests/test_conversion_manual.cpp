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

    struct cieref {
        col_t rgb;
        col_t xyz;
        col_t lab;
        col_t lch;
    };

    //  sourced from Bruce Lindbloom's CIE Color Calculator [10]
    //  [10] http://www.brucelindbloom.com/index.html?Eqn_RGB_XYZ_Matrix.html
    std::vector<cieref> refs = {
        {
            { 1.f, 0.f, 0.f },
            { 0.412456, 0.212673, 0.019334 },
            { 53.2408, 80.0925, 67.2032 },
            { 53.2408, 104.5518, 39.9990 }
        },
        {
            { 0.f, 1.f, 0.f },
            { 0.357576f, 0.715152f, 0.119192f },
            { 87.7347f, -86.1827f, 83.1793f },
            { 87.7347f, 119.7759f, 136.0160f }
        },
        {
            { 0.f, 0.f, 1.f },
            { 0.180437f, 0.072175f, 0.950304f },
            { 32.2970f, 79.1875f, -107.8602f },
            { 32.2970f, 133.8076f, 306.2849f }
        },
        {
            { 0.7f, 0.3f, 0.3f },
            { 0.224179, 0.152938, 0.086990 },
            { 46.0340, 41.5389, 20.8161 },
            { 46.0340, 46.4628, 26.6165 }
        },
        {
            { 0.1f, 0.6f, 0.4f },
            { 0.142013f, 0.239531f, 0.164427 },
            { 56.0408f, -45.2026f, 17.7037 },
            { 56.0408f, 48.5459, 158.6121 }
        }
    };


    for ( const auto& ref : refs )
    {
        //  shorthands for aligned CAPTURE formatting

        const auto& rrgb = ref.rgb;
        const auto& rxyz = ref.xyz;
        const auto& rlab = ref.lab;
        const auto& rlch = ref.lch;

        //  forward

        const auto rgb1 = ref.rgb;
        const auto xyz1 = xyz::fromRgb( rgb1 );
        const auto lab1 = lab::fromXyz( xyz1 );
        const auto lch1 = lch::fromLab( lab1 );

        CAPTURE( rgb1, xyz1, rxyz, lab1, rlab, lch1, rlch );
        REQUIRE( fuzzyEqual( xyz1, ref.xyz ) );
        REQUIRE( fuzzyEqual( lab1, ref.lab ) );
        REQUIRE( fuzzyEqual( lch1, ref.lch ) );

        //  backward

        const auto lch2 = ref.lch;
        const auto lab2 = lab::fromLch( lch2 );
        const auto xyz2 = xyz::fromLab( lab2 );
        const auto rgb2 = rgb::fromXyz( xyz2 );

        CAPTURE( lch2, lab2, rlab, xyz2, rxyz, rgb2, rrgb );
        REQUIRE( fuzzyEqual( lab2, ref.lab ) );
        REQUIRE( fuzzyEqual( xyz2, ref.xyz ) );
        REQUIRE( fuzzyEqual( rgb1, ref.rgb ) );
    }
}
