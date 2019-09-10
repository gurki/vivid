#include "vivid/vivid.h"
#include <algorithm>
#include <fstream>
#include <iomanip>


int main( int, char*[] )
{
    using namespace vivid;

    std::vector<ColorMap::Preset> defaults = {
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

    for ( const auto& type : defaults )
    {
        ColorMap cmap( type );
        cmap.interpolation = ColorMap::InterpolationLch;

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
