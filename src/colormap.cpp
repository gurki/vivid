#include "vivid/colormap.h"
#include "vivid/conversion.h"
#include "vivid/functions.h"

#include <glm/common.hpp>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

namespace tq {


////////////////////////////////////////////////////////////////////////////////
bool ColorMap::load( const std::string& file )
{
    stops_.clear();

    std::ifstream fin;
    fin.open( file );
    auto data = nlohmann::json::parse( fin );

    for ( const auto& item : data ) {
        glm::vec3 col( item[ 0 ], item[ 1 ], item[ 2 ] );
        stops_.push_back( col );
    }

    return false;
}


////////////////////////////////////////////////////////////////////////////////
glm::vec3 ColorMap::at( const float t )
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
        case HSV: return tq::rgb::lerpHsv( stops_[ k ], stops_[ k + 1 ], u );
        case CIELCh: return tq::rgb::lerpHcl( stops_[ k ], stops_[ k + 1 ], u );
    }

    return {};
}


}   //  ::tq
