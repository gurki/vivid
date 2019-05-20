#include "vivid/vivid.h"
#include <fstream>


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
        fout.open( name + ".h" );
        std::replace( name.begin(), name.end(), '-', '_' );

        fout << "#pragma once \n";
        fout << "\n";
        fout << "#include \"vivid/types.h\" \n";
        fout << "#include <vector> \n";
        fout << "\n";
        fout << "namespace vivid::data { \n";
        fout << "\n\n";
        fout << "static const std::vector<col_t> " << name << " = \n";
        fout << "{ \n";

        for ( size_t i = 0; i < cmap.numStops(); i++ )
        {
            const auto& stop = cmap.stops().at( i );
            fout << "    { " << stop.x << ", " << stop.y << ", " << stop.z << " }";

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
