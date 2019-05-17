#include "vivid/vivid.h"

#include <QImage>
#include <QColor>
#include <QDir>

#include <iostream>
#include <functional>
#include <sstream>


int main( int, char* argv[] )
{
    tq::ColorTable::initialize();

    QDir dir( argv[ 0 ] );
    dir.cdUp();
    dir.mkdir( "output/" );
    dir.cd( "output/" );

    //  introduction

    tq::ColorMap hslMap( tq::ColorMap::PresetHsl );
    std::cout << tq::ansi::colorize( "vivid", hslMap ) << std::endl;
    std::cout << std::endl;

    //  colormaps

    dir.mkpath( "colormaps/" );
    dir.cd( "colormaps/" );

    std::vector<tq::ColorMap::Preset> defaults = {
        tq::ColorMap::PresetBlueYellow,
        tq::ColorMap::PresetCoolWarm,
        tq::ColorMap::PresetInferno,
        tq::ColorMap::PresetMagma,
        tq::ColorMap::PresetPlasma,
        tq::ColorMap::PresetRainbow,
        tq::ColorMap::PresetHsl,
        tq::ColorMap::PresetHslPastel,
        tq::ColorMap::PresetViridis,
        tq::ColorMap::PresetVivid
    };

    for ( const auto& type : defaults )
    {
        tq::ColorMap cmap( type );
        cmap.interpolation = tq::ColorMap::InterpolationHcl;
        QImage img( 512, 32, QImage::Format_RGB32 );

        for ( int c = 0; c < img.width(); c++ )
        {
            const float t = c / ( img.width() - 1.f );
            const auto col = glm::vec<3, double>( cmap.at( t ) );
            const QColor qcol = QColor::fromRgbF( col.x, col.y, col.z );

            for ( int r = 0; r < img.height(); r++ ) {
                img.setPixelColor( c, r, qcol );
            }
        }

        img.save( dir.filePath( QString::fromStdString( tq::ColorMap::nameForPreset( type ) + ".png" ) ));
    }

    //  interpolation

    dir.cdUp();
    dir.mkdir( "interpolations/" );
    dir.cd( "interpolations/" );

    using colorlerp_t = std::function< tq::col_t( const tq::col_t&, const tq::col_t&, const float ) >;
    using annotated_colorlerp_t = std::pair<colorlerp_t, std::string>;
    auto lerpHslClamp = []( const tq::col_t& c1, const tq::col_t& c2, const float t ) {
        return tq::rgb::clamp( tq::rgb::lerpHsl( c1, c2, t ) );
    };

    const std::vector<annotated_colorlerp_t> lerps = {
        { tq::rgb::lerp, "lerpRgb" },
        { tq::rgb::lerpHsv, "lerpHsv" },
        { tq::rgb::lerpHsl, "lerpHsl" },
        { tq::rgb::lerpHcl, "lerpHcl" },
        { lerpHslClamp, "lerpHslClamped" }
    };

    static const tq::col_t c1( 0.7f, 0.3f, 0.3f );
    static const tq::col_t c2( 0.1f, 0.6f, 0.4f );

    for ( const auto& lerp: lerps )
    {
        QImage img( 512, 32, QImage::Format_RGB32 );

        for ( int c = 0; c < img.width(); c++ )
        {
            const float t = c / ( img.width() - 1.f );
            const auto col = glm::vec<3, double>( lerp.first( c1, c2, t ) );
            const QColor qcol = QColor::fromRgbF( col.x, col.y, col.z );

            for ( int r = 0; r < img.height(); r++ ) {
                img.setPixelColor( c, r, qcol );
            }
        }

        img.save( dir.filePath( QString::fromStdString( lerp.second + ".png" ) ));
    }

    //  low-level conversions

    static const tq::col_t col( 1.f, 0.7f, 0.5f );
    tq::rgb::spaceRoundtrip( col );
    tq::rgb::typeRoundtrip( col );

    const auto hsl = tq::hsl::fromRgb( col );
    const auto rgb_2 = tq::rgb::fromHsl( hsl );

    std::cout << "rgb_1: " << col << std::endl;
    std::cout << "hsl:   " << hsl << std::endl;
    std::cout << "rgb_2: " << rgb_2 << std::endl;

    //  high-level conversions

    std::cout << std::endl;

    tq::Color color1, color2;
    color1 = tq::Color( c1 );
    color2 = tq::Color( c2 );

    std::cout << color1.hsl() << std::endl;
    std::cout << tq::lerp( color1.hsl(), color2.hsl(), 0.5f ) << std::endl;

    //  encoding

    std::cout << std::endl;
    std::cout << tq::ansi::fg( 3 ) << "yay colors" << tq::ansi::reset << std::endl;
    std::cout << tq::html::fg( "#abc123" ) << "hex hex!" << tq::html::close << std::endl;
    std::cout << tq::html::fg( tq::col8_t( 100, 144, 159 ) ) << "html, aw yes" << tq::html::close << std::endl;
    std::cout << std::endl;

    //  escape codes

    tq::printColorTable();

    //  rainbow text

    tq::ColorMap rainbowMap( tq::ColorMap::PresetRainbow );
    const std::string text = "How can you tell? - Raaaaaaiiiinbooooooowwws.";
    std::cout << tq::ansi::colorize( text, rainbowMap ) << std::endl;

    return EXIT_SUCCESS;
}
