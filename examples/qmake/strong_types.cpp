#include "vivid/vivid.h"
#include "vivid/strong.h"


int main( int, char*[] )
{
    using namespace vivid;

    rgb_t rgb1 = { 1, 2, 3 };
    hsl_t hsl1( 4, 5, 6 );

    rgb_t rgb2( hsl1 );

    lerp( rgb1, rgb1, 0.1f );
    lerp( rgb1, hsl1, 0.2f );

    return EXIT_SUCCESS;
}
