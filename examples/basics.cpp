#include <vivid/vivid.h>
#include <iostream>


int main( int, char* argv[] )
{
    using namespace vivid;

    //  introduction

    const ColorMap hslMap( ColorMap::Preset::Hsl );
    std::cout << ansi::colorize( "vivid", hslMap ) << std::endl;
    std::cout << std::endl;

    //  low-level conversions

    static const rgb_t rgb1( 1.f, 0.7f, 0.5f );
    const auto hsl = hsl::fromRgb( rgb1 );
    const auto rgb2 = rgb::fromHsl( hsl );

    std::cout << rgb1 << " -> " << hsl << " -> " << rgb2 << std::endl;

    //  high-level conversions

    const Color color1 = rgb_t( 0.7f, 0.3f, 0.3f );
    Color color2 = hsl_t( 0.1f, 0.6f, 0.4f );
    color2 = color2.hsv();

    std::cout << color1.quickInfo() << std::endl;
    std::cout << color2.quickInfo() << std::endl;
    std::cout << lerpHsl( color1, color2, 0.7f ).info() << std::endl;

    //  encoding

    std::cout << std::endl;
    std::cout << html::fg( "#abc123" ) << "hex hex!" << html::close << std::endl;
    std::cout << html::fg( color2 ) << "html, aw yes" << html::close << std::endl;
    std::cout << ansi::lightBlue << "yay presets" << ansi::reset << std::endl;
    std::cout << std::endl;

    //  escape codes

    ansi::printColorTable();
    std::cout << std::endl;

    ansi::printColorPresets();
    std::cout << std::endl;

    //  rainbow text

    const ColorMap rainbowMap( ColorMap::Preset::Rainbow );
    const std::string text = "How can you tell? - Raaaaaaiiiinbooooooowwws.";
    std::cout << ansi::colorize( text, rainbowMap ) << std::endl;

    return EXIT_SUCCESS;
}
