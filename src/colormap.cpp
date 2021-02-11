#include "vivid/colormap.h"
#include "vivid/conversion.h"
#include "vivid/utility.h"
#include "vivid/data.h"
#include "vivid/stream.h"
#include "vivid/interpolation.h"

#include <glm/common.hpp>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <cmath>
#include <string>

namespace vivid {


////////////////////////////////////////////////////////////////////////////////
ColorMap::ColorMap( const Preset preset )
{
    switch ( preset )
    {
        case Preset::BlueYellow: stops_ = data::blue_yellow; break;
        case Preset::CoolWarm: stops_ = data::cool_warm; break;
        case Preset::Hsl: stops_ = data::hsl; break;
        case Preset::HslPastel: stops_ = data::hsl_pastel; break;
        case Preset::Inferno: stops_ = data::inferno; break;
        case Preset::Magma: stops_ = data::magma; break;
        case Preset::Plasma: stops_ = data::plasma; break;
        case Preset::Rainbow: stops_ = data::rainbow; break;
        case Preset::Turbo: stops_ = data::turbo; break;
        case Preset::Viridis: stops_ = data::viridis; break;
        case Preset::Vivid: stops_ = data::vivid; break;
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

    const auto u = std::fmod( sf, 1.f );

    switch ( interpolation )
    {
        case Interpolation::Nearest: return stops_[ k ];
        case Interpolation::Linear: return lerp( stops_[ k ], stops_[ k + 1 ], u );
        case Interpolation::Hsv: return rgb::fromHsv( lerp(
            hsv::fromRgb( stops_[ k ] ),
            hsv::fromRgb( stops_[ k + 1 ] ),
            u
        ));
        case Interpolation::Hsl: return rgb::fromHsl( lerp(
            hsl::fromRgb( stops_[ k ] ),
            hsl::fromRgb( stops_[ k + 1 ] ),
            u
        ));
        case Interpolation::Lch: return rgb::saturate(
            srgb::fromLch( lerp(
                lch::fromSrgb( stops_[ k ] ),
                lch::fromSrgb( stops_[ k + 1 ] ),
                u
            )
        ));
    }

    return {};
}


////////////////////////////////////////////////////////////////////////////////
std::string ColorMap::nameForPreset( const Preset preset )
{
    switch ( preset )
    {
        case Preset::BlueYellow: return "blue-yellow";
        case Preset::CoolWarm: return "cool-warm";
        case Preset::Hsl: return "hsl";
        case Preset::HslPastel: return "hsl-pastel";
        case Preset::Inferno: return "inferno";
        case Preset::Magma: return "magma";
        case Preset::Plasma: return "plasma";
        case Preset::Rainbow: return "rainbow";
        case Preset::Turbo: return "turbo";
        case Preset::Viridis: return "viridis";
        case Preset::Vivid: return "vivid";
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
        srgb_t col( item.at( 0 ).get<float>(), item.at( 1 ).get<float>(), item.at( 2 ).get<float>() );
        stops.push_back( col );
    }

    return stops;
}


}   //  ::vivid
