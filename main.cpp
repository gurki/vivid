#include "vivid/color.h"
#include "vivid/colormap.h"

#include <QImage>
#include <QColor>

#include <iostream>


int main( int argc, char* argv[] )
{
    tq::ColorMap cm;
    cm.load( "C:/Users/tgurdan/disk/code/ATL/vivid/res/colormaps/viridis.json" );

    QImage img( 4096, 128, QImage::Format_RGB32 );

    for ( int c = 0; c < img.width(); c++ )
    {
        const float t = c / ( img.width() - 1.f );
        const glm::vec3 col = cm.at( t );
        const QColor qcol = QColor::fromRgbF( col.x, col.y, col.z );

        for ( int r = 0; r < img.height(); r++ ) {
            img.setPixelColor( c, r, qcol );
        }
    }

    img.save( "viridis.png" );

    return EXIT_SUCCESS;
}
