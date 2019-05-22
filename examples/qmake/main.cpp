#include "vivid/vivid.h"
#include "vivid/profiles.h"

#include <QImage>
#include <QColor>
#include <QDir>

#include <iostream>
#include <functional>
#include <sstream>
#include <fstream>


int main( int, char* argv[] )
{
    using namespace vivid;

    QDir dir( argv[ 0 ] );
    dir.cdUp();
    dir.mkdir( "output/" );
    dir.cd( "output/" );

    //  introduction

    ColorMap hslMap( ColorMap::PresetHsl );
    std::cout << ansi::colorize( "vivid", hslMap ) << std::endl;
    std::cout << std::endl;

    //  colormaps

    dir.mkpath( "colormaps/" );
    dir.cd( "colormaps/" );

    std::vector<ColorMap::Preset> presets = {
        ColorMap::PresetBlueYellow,
        ColorMap::PresetCoolWarm,
        ColorMap::PresetInferno,
        ColorMap::PresetMagma,
        ColorMap::PresetPlasma,
        ColorMap::PresetRainbow,
        ColorMap::PresetHsl,
        ColorMap::PresetHslPastel,
        ColorMap::PresetViridis,
        ColorMap::PresetVivid
    };

    for ( const auto& preset : presets )
    {
        std::cout << "Exporting " << ColorMap::nameForPreset( preset ) << " ..." << std::endl;

        ColorMap cmap( preset );
        cmap.interpolation = ColorMap::InterpolationLch;
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

        img.save( dir.filePath( QString::fromStdString( ColorMap::nameForPreset( preset ) + ".png" ) ));
    }

    //  interpolation

    dir.cdUp();
    dir.mkdir( "interpolations/" );
    dir.cd( "interpolations/" );

    using lerp_t = std::function< Color( const Color&, const Color&, const float ) >;
    using alerp_t = std::pair<lerp_t, std::string>; //  annotated lerp function
    auto lerpHslClamp = []( const Color& c1, const Color& c2, const float t ) -> Color {
        return rgb::clamp( rgb_t( lerpHsl( c1, c2, t ).value() ) );
    };

    const std::vector<alerp_t> lerps = {
        { lerpRgb, "lerpRgb" },
        { lerpHsv, "lerpHsv" },
        { lerpHsl, "lerpHsl" },
        { lerpLch, "lerpLch" },
        { lerpHslClamp, "lerpHslClamped" }
    };

    static const col_t c1( 0.7f, 0.3f, 0.3f );
    static const col_t c2( 0.1f, 0.6f, 0.4f );

    for ( const auto& lerp: lerps )
    {
        std::cout << "Exporting " << lerp.second << " ..." << std::endl;
        QImage img( 512, 32, QImage::Format_RGB32 );

        for ( int c = 0; c < img.width(); c++ )
        {
            const float t = c / ( img.width() - 1.f );
            const auto col = lerp.first( c1, c2, t ).value();
            const QColor qcol = QColor::fromRgbF( col.x, col.y, col.z );

            for ( int r = 0; r < img.height(); r++ ) {
                img.setPixelColor( c, r, qcol );
            }
        }

        img.save( dir.filePath( QString::fromStdString( lerp.second + ".png" ) ));
    }

    //  low-level conversions

    static const col_t col( 1.f, 0.7f, 0.5f );
    const hsl_t hsl = hsl::fromRgb( rgb_t( col ) );
    const rgb_t rgb_2 = rgb::fromHsl( hsl );

    std::cout << col << " -> " << hsl << " -> " << rgb_2 << std::endl;

    //  high-level conversions

    Color color1, color2;
    color1 = Color( c1 );
    color2 = Color( c2 );

    std::cout << color1.hsl() << std::endl;
    std::cout << lerp( color1.hsl(), color2.hsl(), 0.5f ) << std::endl;

    //  encoding

    std::cout << std::endl;
    std::cout << ansi::fg( 3 ) << "yay colors" << ansi::reset << std::endl;
    std::cout << html::fg( "#abc123" ) << "hex hex!" << html::close << std::endl;
    std::cout << html::fg( col8_t( 100, 144, 159 ) ) << "html, aw yes" << html::close << std::endl;
    std::cout << std::endl;

    //  escape codes

//    printColorTable();

    //  wide gamut conversions

    adobe_t adobe = { 1, 0, 0 };
    srgb_t srgb = { 1, 0, 0 };
    std::cout << srgb::fromAdobe( adobe ) << std::endl;
    std::cout << ( 255.f * adobe::fromSrgb( srgb ) ) << std::endl;

    //  rainbow text

    ColorMap rainbowMap( ColorMap::PresetRainbow );
    const std::string text = "How can you tell? - Raaaaaaiiiinbooooooowwws.";
    std::cout << ansi::colorize( text, rainbowMap ) << std::endl;

    return EXIT_SUCCESS;
}
