#include "utility.h"

#include "vivid/conversion.h"
#include "vivid/stream.h"

#include "catch.hpp"


////////////////////////////////////////////////////////////////////////////////
TEST_CASE( "Manual Conversions", "[conversions]" )
{
    using namespace vivid;

    struct cieref {
        srgb_t rgb;
        xyz_t xyz;
        lab_t lab;
        lch_t lch;
    };

    //  sourced from Bruce Lindbloom's CIE Color Calculator [10]
    //  [10] http://www.brucelindbloom.com/index.html?Eqn_RGB_XYZ_Matrix.html
    std::vector<cieref> refs = {
        {
            { 0.f, 0.f, 0.f },
            { 0.f, 0.f, 0.f },
            { 0.f, 0.f, 0.f },
            { 0.f, 0.f, 0.f }
        },
        {
            { 1.f, 1.f, 1.f },
            { 0.950470f, 1.f, 1.088830f },
            { 100.f, 0.f, 0.f },
            { 100.f, 0.f, 0.f } //  source: 100, 0, 270
        },
        {
            { 1.f, 0.f, 0.f },
            { 0.412456f, 0.212673f, 0.019334f },
            { 53.2408f, 80.0925f, 67.2032f },
            { 53.2408f, 104.5518f, 39.9990f }
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
            { 1.f, 1.f, 0.f },
            { 0.770033f, 0.927825f, 0.138526f },
            { 97.1393f, -21.5537f, 94.4780f },
            { 97.1393f, 96.9054f, 102.8512f }
        },
        {
            { 0.f, 1.f, 1.f },
            { 0.538014f, 0.787327f, 1.069496f },
            { 91.1132f, -48.0875f, -14.1312f },
            { 91.1132f, 50.1209f, 196.3762f }
        },
        {
            { 1.f, 0.f, 1.f },
            { 0.592894f, 0.284848f, 0.969638f },
            { 60.3242f, 98.2343f, -60.8249f },
            { 60.3242f, 115.5407f, 328.2350f }
        },
        {
            { 0.7f, 0.3f, 0.3f },
            { 0.224179f, 0.152938f, 0.086990f },
            { 46.0340f, 41.5389f, 20.8161f },
            { 46.0340f, 46.4628f, 26.6165f }
        },
        {
            { 0.1f, 0.6f, 0.4f },
            { 0.142013f, 0.239531f, 0.164427f },
            { 56.0408f, -45.2026f, 17.7037f },
            { 56.0408f, 48.5459f, 158.6121f }
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
        const auto xyz1 = xyz::fromSrgb( rgb1 );
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
        const auto rgb2 = srgb::fromXyz( xyz2 );

        CAPTURE( lch2, lab2, rlab, xyz2, rxyz, rgb2, rrgb );
        REQUIRE( fuzzyEqual( lab2, ref.lab ) );
        REQUIRE( fuzzyEqual( xyz2, ref.xyz ) );
        REQUIRE( fuzzyEqual( rgb1, ref.rgb ) );
    }
}
