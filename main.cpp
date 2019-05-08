#include "vivid/colormap.h"
#include "vivid/conversion.h"

#include <glm/gtx/string_cast.hpp>

#include <QImage>
#include <QColor>

#include <iostream>


int main( int, char*[] )
{
    tq::ColorMap cmap;
    cmap.load( VIVID_ROOT_PATH "/res/colormaps/viridis.json" );
    cmap.interpolation = tq::ColorMap::Linear;

    QImage img( 4096, 128, QImage::Format_RGB32 );

    for ( int c = 0; c < img.width(); c++ )
    {
        const float t = c / ( img.width() - 1.f );
        const auto col = cmap.at( t );
        const QColor qcol = QColor::fromRgbF( col.x, col.y, col.z );

        for ( int r = 0; r < img.height(); r++ ) {
            img.setPixelColor( c, r, qcol );
        }
    }

    img.save( "viridis.png" );

    tq::col_t col( 1.f, 0.7f, 0.5f );
    tq::rgb::spaceRoundtrip( col );
    tq::rgb::typeRoundtrip( col );

    return EXIT_SUCCESS;
}
