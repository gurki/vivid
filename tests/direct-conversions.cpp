#include "vivid/conversion.h"
#include "vivid/stream.h"
#include "vivid/colortable.h"

#include "utility.h"
#include "catch.hpp"

using namespace tq;

static const size_t fuzzIters = 10'000;


////////////////////////////////////////////////////////////////////////////////
TEST_CASE( "Direct Conversions", "[conversions]" )
{
    ColorTable::initialize();

    SECTION( "RGB8 -> RGB" )
    {
        for ( size_t i = 0; i < fuzzIters; i++ )
        {
            const col8_t rgb8 = tq::rgb8::rand();
            const QColor qcol = { rgb8.x, rgb8.y, rgb8.z };
            const col_t rgb = tq::rgb::fromRgb8( rgb8 );
            const col_t qrgb = tq::rgb::fromQt( qcol );

            CAPTURE( rgb8, rgb, qrgb );
            REQUIRE( fuzzyEqual( rgb, qrgb ) );
        }
    }

    SECTION( "HSV -> RGB" )
    {
        for ( size_t i = 0; i < fuzzIters; i++ )
        {
            const col_t hsv = tq::rgb::rand();
            const QColor qhsv = QColor::fromHsvF( hsv.x, hsv.y, hsv.z );
            const col_t rgb = tq::rgb::fromHsv( hsv );
            const col_t qrgb = tq::rgb::fromQt( qhsv );

            CAPTURE( hsv, rgb, qrgb );
            REQUIRE( fuzzyEqual( rgb, qrgb ) );
        }
    }

    SECTION( "HSL -> RGB" )
    {
        for ( size_t i = 0; i < fuzzIters; i++ )
        {
            const col_t hsl = tq::rgb::rand();
            const QColor qhsl = QColor::fromHslF( hsl.x, hsl.y, hsl.z );
            const col_t rgb = tq::rgb::fromHsl( hsl );
            const col_t qrgb = tq::rgb::fromQt( qhsl );

            CAPTURE( hsl, rgb, qrgb );
            REQUIRE( fuzzyEqual( rgb, qrgb ) );
        }
    }

    SECTION( "RGB -> HSV" )
    {
        for ( size_t i = 0; i < fuzzIters; i++ )
        {
            const col_t col = tq::rgb::rand();
            const QColor qcol  = QColor::fromRgbF( col.x, col.y, col.z );
            const col_t tar = tq::hsv::fromRgb( col );
            const col_t qtar = { qcol.hueF(), qcol.saturationF(), qcol.valueF() };

            CAPTURE( col, tar, qtar );
            REQUIRE( fuzzyHueEqual( tar, qtar ) );
        }
    }

    SECTION( "RGB -> HSL" )
    {
        for ( size_t i = 0; i < fuzzIters; i++ )
        {
            const col_t col = tq::rgb::rand();
            const QColor qcol  = QColor::fromRgbF( col.x, col.y, col.z );
            const col_t tar = tq::hsl::fromRgb( col );
            const col_t qtar = { qcol.hslHueF(), qcol.hslSaturationF(), qcol.lightnessF() };

            CAPTURE( col, tar, qtar );
            REQUIRE( fuzzyHueEqual( tar, qtar ) );
        }
    }

    SECTION( "RGB <-> XYZ <-> LAB <-> HCL" )
    {
        for ( size_t i = 0; i < fuzzIters; i++ )
        {
            const col_t src = tq::rgb::rand();
            const col_t xyz_1 = xyz::fromRgb( src );
            const col_t lab_1 = lab::fromXyz( xyz_1 );
            const col_t lch_1 = hcl::fromLab( lab_1 );
            const col_t lab_2 = lab::fromHcl( lch_1 );
            const col_t xyz_2 = xyz::fromLab( lab_2 );
            const col_t tar = rgb::fromXyz( xyz_2 );

            CAPTURE( src, tar );
            REQUIRE( fuzzyEqual( src, tar ) );
        }
    }

    SECTION( "Index <-> Hex <-> RGB8 <-> RGB32 <-> RGB" )
    {
        for ( size_t i = 0; i < fuzzIters; i++ )
        {
            const uint8_t src = randi();
            const auto hex_1 = tq::hex::fromIndex( src );
            const auto rgb8_1 = tq::rgb8::fromHex( hex_1 );
            const auto rgb32_1 = tq::rgb32::fromRgb8( rgb8_1 );
            const auto rgb = tq::rgb::fromRgb32( rgb32_1 );
            const auto rgb32_2 = tq::rgb32::fromRgb( rgb );
            const auto rgb8_2 = tq::rgb8::fromRgb32( rgb32_2 );
            const auto hex_2 = tq::hex::fromRgb8( rgb8_2 );

            //  NOTE(tgurdan): hex values are not unique, so can't check indices
            CAPTURE( int( src ), hex_1, hex_2 );
            REQUIRE( hex_1 == hex_2 );
        }
    }

    //  NOTE(tgurdan): can't test index <-> name conversion really, as names are not unique
}
