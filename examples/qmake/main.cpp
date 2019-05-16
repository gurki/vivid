#include "vivid/vivid.h"
#include <glm/gtx/string_cast.hpp>

#include <QImage>
#include <QColor>
#include <QDir>

#include <iostream>
#include <functional>
#include <sstream>


std::string rainbowText( const std::string& text );


int main( int, char* argv[] )
{
    tq::ColorTable::initialize();

    QDir dir( argv[ 0 ] );

    //  colormaps

    dir.cdUp();
    dir.mkdir( "colmaps/" );
    dir.cd( "colmaps/" );

    std::vector<std::string> cmapNames = {
        "inferno", "magma", "plasma", "viridis"
    };

    for ( const auto& name : cmapNames )
    {
        tq::ColorMap cmap;
        cmap.load( VIVID_ROOT_PATH "/res/colormaps/" + name + ".json" );
        cmap.interpolation = tq::ColorMap::Hcl;

        QImage img( 512, 128, QImage::Format_RGB32 );

        for ( int c = 0; c < img.width(); c++ )
        {
            const float t = c / ( img.width() - 1.f );
            const auto col = glm::vec<3, double>( cmap.at( t ) );
            const QColor qcol = QColor::fromRgbF( col.x, col.y, col.z );

            for ( int r = 0; r < img.height(); r++ ) {
                img.setPixelColor( c, r, qcol );
            }
        }

        img.save( dir.filePath( QString::fromStdString( name + ".png" ) ));
    }

    //  conversions

    dir.cdUp();
    dir.mkdir( "interps/" );
    dir.cd( "interps/" );

    static const tq::col_t col( 1.f, 0.7f, 0.5f );
    tq::rgb::spaceRoundtrip( col );
    tq::rgb::typeRoundtrip( col );

    const auto hsl = tq::hsl::fromRgb( col );
    const auto rgb2 = tq::rgb::fromHsl( hsl );

    std::cout << "rgb1: " << glm::to_string( col ) << std::endl;
    std::cout << "hsl:  " << glm::to_string( hsl ) << std::endl;
    std::cout << "rgb2: " << glm::to_string( rgb2 ) << std::endl;

    //  interpolation

    using colorlerp_t = std::function< tq::col_t( const tq::col_t&, const tq::col_t&, const float ) >;
    using annotated_colorlerp_t = std::pair<colorlerp_t, std::string>;
    const std::vector<annotated_colorlerp_t> lerps = {
        { tq::rgb::lerp, "lerpRgb" },
        { tq::rgb::lerpHsv, "lerpHsv" },
        { tq::rgb::lerpHsl, "lerpHsl" },
        { tq::rgb::lerpHcl, "lerpHcl" }
    };

    static const tq::col_t c1( 0.7f, 0.3f, 0.3f );
    static const tq::col_t c2( 0.1f, 0.6f, 0.4f );

    for ( const auto& lerp: lerps )
    {
        QImage img( 512, 128, QImage::Format_RGB32 );

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

    //  escape codes

    tq::printColorTable();

    //  rainbow text

    std::cout << rainbowText( "How can you tell? - Raaaaaaiiiinbooooooowwws." ) << std::endl;;

    return EXIT_SUCCESS;
}


////////////////////////////////////////////////////////////////////////////////
std::string rainbowText( const std::string& text )
{
    using namespace tq;

    std::stringstream ss;
    const float n = text.size();

    for ( size_t i = 0; i < n; i++ ) {
        const auto k = uint8_t( ( i / n ) * 255.f );
        const auto id = index::fromRgb( rgb::clamp( rgb::rainbow( k ) ));
        ss << "\x1b[38;5;" + std::to_string( id ) + "m" << text[ i ];
    }

    ss << "\x1b[0m";
    return ss.str();
}
