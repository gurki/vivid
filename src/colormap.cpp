#include "vivid/colormap.h"
#include "vivid/conversion.h"
#include "vivid/functions.h"
#include "vivid/data.h"
#include "vivid/stream.h"

#include <glm/common.hpp>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

namespace vivid {


////////////////////////////////////////////////////////////////////////////////
ColorMap::ColorMap( const Preset preset )
{
    switch ( preset )
    {
        case PresetBlueYellow: stops_ = data::blue_yellow; break;
        case PresetCoolWarm: stops_ = data::cool_warm; break;
        case PresetInferno: stops_ = data::inferno; break;
        case PresetMagma: stops_ = data::magma; break;
        case PresetPlasma: stops_ = data::plasma; break;
        case PresetRainbow: stops_ = data::rainbow; break;
        case PresetHsl: stops_ = data::hsl; break;
        case PresetHslPastel: stops_ = data::hsl_pastel; break;
        case PresetViridis: stops_ = data::viridis; break;
        case PresetVivid: stops_ = data::vivid; break;
    }
}


////////////////////////////////////////////////////////////////////////////////
ColorMap::ColorMap( const std::string& filename ) {
    stops_ = loadFromFile( filename );
}


////////////////////////////////////////////////////////////////////////////////
srgb_t ColorMap::at( const float t ) const
{
    if ( empty() ) {
        return {};
    }

    const size_t steps = stops_.size() - 1;
    const float s = glm::clamp( t, 0.f, 1.f );
    const float sf = s * steps;
    const size_t k = size_t( glm::floor( sf ) );

    if ( k + 1 == stops_.size() ) {
        return stops_.back();
    }

    const auto u = std::fmodf( sf, 1.f );

    switch ( interpolation )
    {
        case InterpolationNearest: return stops_[ k ];
        case InterpolationLinear: return vivid::lerp( stops_[ k ], stops_[ k + 1 ], u );
        case InterpolationHsv: return vivid::lerpHsv( stops_[ k ], stops_[ k + 1 ], u );
        case InterpolationHsl: return vivid::lerpHsl( stops_[ k ], stops_[ k + 1 ], u );
        case InterpolationLch: return vivid::lerpLch( stops_[ k ], stops_[ k + 1 ], u );
    }

    return {};
}


////////////////////////////////////////////////////////////////////////////////
std::string ColorMap::nameForPreset( const Preset preset )
{
    switch ( preset )
    {
        case PresetBlueYellow: return "blue-yellow";
        case PresetCoolWarm: return "cool-warm";
        case PresetInferno: return "inferno";
        case PresetMagma: return "magma";
        case PresetPlasma: return "plasma";
        case PresetRainbow: return "rainbow";
        case PresetHsl: return "hsl";
        case PresetHslPastel: return "hsl-pastel";
        case PresetViridis: return "viridis";
        case PresetVivid: return "vivid";
    }

    return {};
}


////////////////////////////////////////////////////////////////////////////////
std::vector<srgb_t> ColorMap::loadFromFile( const std::string& filename )
{
    std::ifstream fin;
    fin.open( filename );

    if ( ! fin.is_open() ) {
        return {};
    }

    nlohmann::json data;

    try {
        data = nlohmann::json::parse( fin );
    } catch ( const std::exception& ) {
        return {};
    }

    std::vector<srgb_t> stops;
    stops.reserve( data.size() );

    for ( const auto& item : data ) {
        srgb_t col( item[ 0 ], item[ 1 ], item[ 2 ] );
        stops.push_back( col );
    }

    return stops;
}


}   //  ::vivid
