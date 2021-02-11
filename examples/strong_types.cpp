#include "vivid/vivid.h"


int main( int, char*[] )
{
    using namespace vivid;

    //  construction
    rgb_t rgb1( 1, 2, 3 );      //  explicit value initialization
    hsl_t hsl1 = { 4, 5, 6 };   //  implicit value initialization
    rgb_t rgb2 = rgb1;          //  copy

    //  inheritance
    col_t col = { 0, 0, 0 };
//    rgb1 = col;             //  invalid implicit cast to child class
//    rgb1 = rgb_t( col );    //  invalid explicit cast to child class
    col = rgb1;             //  cast to base class

    //  interpolation
    lerp( rgb1, rgb1, 0.1f );   //  lerp in matching color space
//    lerp( rgb1, hsl1, 0.2f );   //  invalid lerp of colors in different spaces
    lerp( lch_t( rgb1 ), lch_t( rgb2 ), 0.5f );

    return EXIT_SUCCESS;
}
