#include "vivid/colormap.h"
#include "vivid/conversion.h"
#include "vivid/functions.h"

#include <glm/common.hpp>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

namespace tq {


////////////////////////////////////////////////////////////////////////////////
glm::vec3 ColorMap::at( const float t ) const
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
        case Nearest: return stops_[ k ];
        case Linear: return tq::rgb::lerp( stops_[ k ], stops_[ k + 1 ], u );
        case Hsv: return tq::rgb::lerpHsv( stops_[ k ], stops_[ k + 1 ], u );
        case Hsl: return tq::rgb::lerpHsl( stops_[ k ], stops_[ k + 1 ], u );
        case Hcl: return tq::rgb::lerpHcl( stops_[ k ], stops_[ k + 1 ], u );
    }

    return {};
}


////////////////////////////////////////////////////////////////////////////////
std::string ColorMap::nameForDefault( const DefaultType type )
{
    switch ( type )
    {
        case BlueYellow: return "blue-yellow";
        case CoolWarm: return "cool-warm";
        case Inferno: return "inferno";
        case Magma: return "magma";
        case Plasma: return "plasma";
        case Rainbow: return "rainbow";
        case Viridis: return "viridis";
        case Vivid: return "vivid";
    }

    return {};
}


////////////////////////////////////////////////////////////////////////////////
ColorMap ColorMap::loadDefault( const DefaultType type ) {
    const std::string name = nameForDefault( type );
    return loadFromFile( VIVID_ROOT_PATH "/res/colormaps/" + name + ".json" );
}


////////////////////////////////////////////////////////////////////////////////
ColorMap ColorMap::loadFromFile( const std::string& file )
{
    std::ifstream fin;
    fin.open( file );

    if ( ! fin.is_open() ) {
        return {};
    }

    nlohmann::json data;

    try {
        data = nlohmann::json::parse( fin );
    } catch ( const std::exception& ) {
        return {};
    }

    ColorMap cmap;

    for ( const auto& item : data ) {
        glm::vec3 col( item[ 0 ], item[ 1 ], item[ 2 ] );
        cmap.stops_.push_back( col );
    }

    return cmap;
}


}   //  ::tq
