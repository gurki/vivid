#include "utility.h"
#include "catch.hpp"

#include "vivid/conversion.h"
#include "vivid/stream.h"

#include <glm/glm.hpp>
#include <QColor>


////////////////////////////////////////////////////////////////////////////////
namespace vivid::rgb {
    inline col_t fromQt( const QColor& qcol ) {
        return { qcol.redF(), qcol.greenF(), qcol.blueF() };
    }
}


////////////////////////////////////////////////////////////////////////////////
TEST_CASE( "Direct Conversions", "[conversions]" )
{
    using namespace vivid;
    static const size_t fuzzIters = 10'000;

    SECTION( "RGB8 -> RGB" )
    {
        for ( size_t i = 0; i < fuzzIters; i++ )
        {
            const col8_t rgb8 = vivid::rgb8::rand();
            const QColor qcol = { rgb8.x, rgb8.y, rgb8.z };
            const col_t rgb = vivid::rgb::fromRgb8( rgb8 );
            const col_t qrgb = vivid::rgb::fromQt( qcol );

            CAPTURE( rgb8, rgb, qrgb );
            REQUIRE( fuzzyEqual( rgb, qrgb ) );
        }
    }

    SECTION( "HSV -> RGB" )
    {
        for ( size_t i = 0; i < fuzzIters; i++ )
        {
            const col_t hsv = vivid::rgb::rand();
            const QColor qhsv = QColor::fromHsvF( hsv.x, hsv.y, hsv.z );
            const col_t rgb = vivid::rgb::fromHsv( hsv );
            const col_t qrgb = vivid::rgb::fromQt( qhsv );

            CAPTURE( hsv, rgb, qrgb );
            REQUIRE( fuzzyEqual( rgb, qrgb ) );
        }
    }

    SECTION( "HSL -> RGB" )
    {
        for ( size_t i = 0; i < fuzzIters; i++ )
        {
            const col_t hsl = vivid::rgb::rand();
            const QColor qhsl = QColor::fromHslF( hsl.x, hsl.y, hsl.z );
            const col_t rgb = vivid::rgb::fromHsl( hsl );
            const col_t qrgb = vivid::rgb::fromQt( qhsl );

            CAPTURE( hsl, rgb, qrgb );
            REQUIRE( fuzzyEqual( rgb, qrgb ) );
        }
    }

    SECTION( "RGB -> HSV" )
    {
        for ( size_t i = 0; i < fuzzIters; i++ )
        {
            const col_t col = vivid::rgb::rand();
            const QColor qcol  = QColor::fromRgbF( col.x, col.y, col.z );
            const col_t tar = vivid::hsv::fromRgb( col );
            const col_t qtar = { qcol.hueF(), qcol.saturationF(), qcol.valueF() };

            CAPTURE( col, tar, qtar );
            REQUIRE( fuzzyHueEqual( tar, qtar ) );
        }
    }

    SECTION( "RGB -> HSL" )
    {
        for ( size_t i = 0; i < fuzzIters; i++ )
        {
            const col_t col = vivid::rgb::rand();
            const QColor qcol  = QColor::fromRgbF( col.x, col.y, col.z );
            const col_t tar = vivid::hsl::fromRgb( col );
            const col_t qtar = { qcol.hslHueF(), qcol.hslSaturationF(), qcol.lightnessF() };

            CAPTURE( col, tar, qtar );
            REQUIRE( fuzzyHueEqual( tar, qtar ) );
        }
    }

    SECTION( "HSL <-> RGB <-> HSV <-> HSL" )
    {
        for ( size_t i = 0; i < fuzzIters; i++ )
        {
            const col_t src = vivid::rgb::rand();
            const auto rgb_1 = vivid::rgb::fromHsl( src );
            const auto hsv_1 = vivid::hsv::fromRgb( rgb_1 );
            const auto hsl_2 = vivid::hsl::fromHsv( hsv_1 );
            const auto hsv_2 = vivid::hsv::fromHsl( hsl_2 );
            const auto rgb_2 = vivid::rgb::fromHsv( hsv_2 );
            const auto tar = vivid::hsl::fromRgb( rgb_2 );

            CAPTURE( src, tar );
            REQUIRE( fuzzyHueEqual( src, tar ) );
        }

/*
        detected failures
            src := col(0.239, 0.000173, 0.998)
            tar := col(0.244, 0.000177, 0.998)
*/
    }

    SECTION( "RGB <-> XYZ <-> LAB <-> LCH" )
    {
        for ( size_t i = 0; i < fuzzIters; i++ )
        {
            const col_t src = vivid::rgb::rand();
            const col_t xyz_1 = xyz::fromRgb( src );
            const col_t lab_1 = lab::fromXyz( xyz_1 );
            const col_t lch_1 = lch::fromLab( lab_1 );
            const col_t lab_2 = lab::fromLch( lch_1 );
            const col_t xyz_2 = xyz::fromLab( lab_2 );
            const col_t tar = rgb::fromXyz( xyz_2 );

            CAPTURE( src, tar );
            REQUIRE( fuzzyEqual( src, tar ) );
        }
    }

    SECTION( "Index -> Hex <-> RGB8 <-> RGB32 <-> RGB" )
    {
        for ( size_t i = 0; i < fuzzIters; i++ )
        {
            const uint8_t src = uint8_t( randi() );
            const auto hex_1 = vivid::hex::fromIndex( src );
            const auto rgb8_1 = vivid::rgb8::fromHex( hex_1 );
            const auto rgb32_1 = vivid::rgb32::fromRgb8( rgb8_1 );
            const auto rgb = vivid::rgb::fromRgb32( rgb32_1 );
            const auto rgb32_2 = vivid::rgb32::fromRgb( rgb );
            const auto rgb8_2 = vivid::rgb8::fromRgb32( rgb32_2 );
            const auto hex_2 = vivid::hex::fromRgb8( rgb8_2 );

            //  NOTE(tgurdan): hex values are not unique, so can't check indices
            CAPTURE( int( src ), hex_1, hex_2 );
            REQUIRE( hex_1 == hex_2 );
        }
    }

    //  NOTE(tgurdan): can't test index <-> name conversion really, as names are not unique

    SECTION( "Ranges" )
    {
        const col_t max = { 100000, 100000, 100000 };
        const col_t min = { - 10000, - 1000000, - 100000 };

        col_t rgb0, xyz0, lab0, lch0;
        col_t rgb1, xyz1, lab1, lch1;
        rgb0 = xyz0 = lab0 = lch0 = max;
        rgb1 = xyz1 = lab1 = lch1 = min;

        for ( size_t i = 0; i < fuzzIters; i++ )
        {
            const col_t src = vivid::rgb::rand();
            const col_t xyz_1 = xyz::fromRgb( src );
            const col_t lab_1 = lab::fromXyz( xyz_1 );
            const col_t lch_1 = lch::fromLab( lab_1 );

            rgb0 = glm::min( rgb0, src );
            xyz0 = glm::min( xyz0, xyz_1 );
            lab0 = glm::min( lab0, lab_1 );
            lch0 = glm::min( lch0, lch_1 );

            rgb1 = glm::max( rgb1, src );
            xyz1 = glm::max( xyz1, xyz_1 );
            lab1 = glm::max( lab1, lab_1 );
            lch1 = glm::max( lch1, lch_1 );

            CAPTURE( rgb0, rgb1, xyz0, xyz1, lab0, lab1, lch0, lch1 );

            REQUIRE( glm::all( glm::greaterThanEqual( rgb0, col_t( 0 ) )));
            REQUIRE( glm::all( glm::greaterThanEqual( xyz0, col_t( 0 ) )));
            REQUIRE( glm::all( glm::greaterThanEqual( lab0, col_t( 0, -86.1827, -107.86 ) )));
            REQUIRE( glm::all( glm::greaterThanEqual( lch0, col_t( 0 ) )));

            REQUIRE( glm::all( glm::lessThanEqual( rgb1, col_t( 1 ) )));
            REQUIRE( glm::all( glm::lessThanEqual( xyz1, col_t( 0.95047f, 1.f, 1.08883f ) )));
            REQUIRE( glm::all( glm::lessThanEqual( lab0, col_t( 100, 98.2343, 94.478 ) )));
            REQUIRE( glm::all( glm::lessThanEqual( lch0, col_t( 100, 140, 360 ) )));
        }
    }
}
