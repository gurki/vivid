#include "vivid/vivid.h"
#include <algorithm>
#include <fstream>
#include <iomanip>


int main( int, char*[] )
{
    using namespace vivid;

    std::vector<ColorMap::Preset> defaults = {
        ColorMap::Preset::BlueYellow,
        ColorMap::Preset::CoolWarm,
        ColorMap::Preset::Inferno,
        ColorMap::Preset::Magma,
        ColorMap::Preset::Plasma,
        ColorMap::Preset::Rainbow,
        ColorMap::Preset::Hsl,
        ColorMap::Preset::HslPastel,
        ColorMap::Preset::Turbo,
        ColorMap::Preset::Viridis,
        ColorMap::Preset::Vivid
    };

    for ( const auto& type : defaults )
    {
        ColorMap cmap( type );
        cmap.interpolation = ColorMap::Interpolation::Lch;

        auto name = ColorMap::nameForPreset( type );
        std::ofstream fout;
        fout.open( "out/" + name + ".h" );
        std::replace( name.begin(), name.end(), '-', '_' );

        fout << "#pragma once \n";
        fout << "\n";
        fout << "#include \"vivid/types.h\" \n";
        fout << "#include <vector> \n";
        fout << "\n";
        fout << "namespace vivid::data { \n";
        fout << "\n\n";
        fout << "static const std::vector<srgb_t> " << name << " = \n";
        fout << "{ \n";

        static auto punc = []( const float t )
        {
            if ( std::fmod( t, 1.f ) != 0.f ) {
                return "f";
            }

            return ".f";
        };

        for ( size_t i = 0; i < cmap.numStops(); i++ )
        {
            const auto& stop = cmap.stops().at( i );
            fout << "    { ";
            fout << stop.x << punc( stop.x ) << ", ";
            fout << stop.y << punc( stop.y ) << ", ";
            fout << stop.z << punc( stop.z ) << " }";

            if ( i + 1 < cmap.numStops() ) {
                fout << ",";
            }

            fout << "\n";
        }
        fout << "}; \n";
        fout << "\n\n";
        fout << "}  //  ::vivid::data";
        fout.close();
    }
}
