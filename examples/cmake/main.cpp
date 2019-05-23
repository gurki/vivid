#include <vivid/vivid.h>
#include <iostream>


int main( int, char* argv[] )
{
    using namespace vivid;

    //  introduction

    const ColorMap hslMap( ColorMap::PresetHsl );
    std::cout << ansi::colorize( "vivid", hslMap ) << std::endl;
    std::cout << std::endl;

    //  low-level conversions

    static const rgb_t rgb1( 1.f, 0.7f, 0.5f );
    const auto hsl = hsl::fromRgb( rgb1 );
    const auto rgb2 = rgb::fromHsl( hsl );

    std::cout << rgb1 << " -> " << hsl << " -> " << rgb2 << std::endl;

    //  high-level conversions

    const Color color1 = { 0.7f, 0.3f, 0.3f };
    const Color color2 = { 0.1f, 0.6f, 0.4f };

    std::cout << color1.hsv() << std::endl;
    std::cout << lerpHsl( color1, color2, 0.5f ) << std::endl;

    //  encoding

    std::cout << std::endl;
    std::cout << ansi::fg( 3 ) << "yay colors" << ansi::reset << std::endl;
    std::cout << html::fg( "#abc123" ) << "hex hex!" << html::close << std::endl;
    std::cout << html::fg( col8_t( 100, 144, 159 ) ) << "html, aw yes" << html::close << std::endl;
    std::cout << std::endl;

    //  escape codes

    printColorTable();

    //  rainbow text

    const ColorMap rainbowMap( ColorMap::PresetRainbow );
    const std::string text = "How can you tell? - Raaaaaaiiiinbooooooowwws.";
    std::cout << ansi::colorize( text, rainbowMap ) << std::endl;

    return EXIT_SUCCESS;
}
