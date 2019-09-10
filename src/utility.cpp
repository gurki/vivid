#include "vivid/utility.h"
#include "vivid/conversion.h"
#include "vivid/stream.h"
#include "vivid/encoding.h"
#include "vivid/colormap.h"
#include "vivid/data/xterm.h"

#include <glm/glm.hpp>
#include <glm/common.hpp>           //  clamp
#include <glm/gtc/constants.hpp>    //  pi
#include <glm/gtx/string_cast.hpp>

#include <iostream>
#include <sstream>
#include <cstdio>
#include <cmath>

namespace vivid {
namespace rgb {


////////////////////////////////////////////////////////////////////////////////
rgb_t saturate( const rgb_t& rgb ) {
    return static_cast<rgb_t>(
        glm::clamp( rgb, 0.f, 1.f )
    );
}


////////////////////////////////////////////////////////////////////////////////
rgb_t clamp( const rgb_t& rgb ) {
    return srgb::fromIndex( index::fromRgb( rgb ) );
}


////////////////////////////////////////////////////////////////////////////////
rgb_t gamma( const rgb_t& rgb, const float gamma ) {
    return static_cast<rgb_t>(
        glm::max( glm::pow( rgb, glm::vec3( gamma ) ), col_t( 0 ) )
    );
}


////////////////////////////////////////////////////////////////////////////////
rgb_t grey( const uint8_t k ) {
    return srgb::fromIndex( data::xterm_grey.at( k ) );
}


}   //  ::vivid::rgb


namespace srgb {


////////////////////////////////////////////////////////////////////////////////
float compound( const float k )
{
    if ( k <= 0.0031308f ) {
        return 12.92f * k;
    }

    return 1.055f * std::pow( k, 1.f / 2.4f ) - 0.055f;
}


////////////////////////////////////////////////////////////////////////////////
float inverseCompound( const float k )
{
    if ( k <= 0.04045f ) {
        return k / 12.92f;
    }

    return std::pow( ( k + 0.055f ) / 1.055f, 2.4f );
}


}   //   ::vivid::srgb


namespace hsl {

////////////////////////////////////////////////////////////////////////////////
hsl_t rainbow( const uint8_t k, const float s, const float l ) {
    const float t = k / 256.f;
    return { t, s, l };
}


////////////////////////////////////////////////////////////////////////////////
hsl_t compact( const col_t& col ) {
    return static_cast<hsl_t>( col / sup );
}


////////////////////////////////////////////////////////////////////////////////
hsl_t readable( const col_t& col ) {
    return static_cast<hsl_t>( glm::round( col * sup ) );
}

}   //  ::vivid::hsl


namespace hsv {

////////////////////////////////////////////////////////////////////////////////
hsv_t compact( const col_t& col ) {
    return static_cast<hsv_t>( col / sup );
}


////////////////////////////////////////////////////////////////////////////////
hsv_t readable( const col_t& col ) {
    return static_cast<hsv_t>( glm::round( col * sup ) );
}

}   //  ::vivid::hsv


namespace xyz {

////////////////////////////////////////////////////////////////////////////////
xyz_t compact( const xyz_t& col ) {
    return static_cast<xyz_t>( col / sup );
}


////////////////////////////////////////////////////////////////////////////////
xyz_t readable( const xyz_t& col ) {
    return static_cast<xyz_t>( glm::round( col * sup ) );
}

}   //  ::vivid::xyz


namespace lch {

////////////////////////////////////////////////////////////////////////////////
lch_t saturate( const lch_t& lch )
{
    return {
        glm::clamp( lch.x, 0.f , 100.f ),
        glm::clamp( lch.y, 0.f , 140.f ),
        glm::clamp( lch.z, 0.f , 360.f )
    };
}

}   //  ::vivid::lch


namespace ansi {


////////////////////////////////////////////////////////////////////////////////
std::string colorize( const std::string& text, const ColorMap& cmap )
{
    if ( cmap.empty() ) {
        return text;
    }

    const float n = float( text.size() );
    std::stringstream ss;

    for ( size_t i = 0; i < n; i++ ) {
        const float t = i / n;
        const uint8_t id = index::fromRgb( cmap.at( t ) );
        ss << ansi::fg( id ) << text[ i ];
    }

    ss << ansi::reset;
    return ss.str();
}


////////////////////////////////////////////////////////////////////////////////
std::string colorize( const col_t& col, const std::string& label )
{
    std::stringstream sstr;
    sstr << ansi::subtleText << label << ansi::symbol << "(" << ansi::text;
    sstr << std::setw( 3 ) << std::right << col.x << ansi::symbol << "," << ansi::text;
    sstr << std::setw( 3 ) << std::right << col.y << ansi::symbol << "," << ansi::text;
    sstr << std::setw( 3 ) << std::right << col.z << ansi::symbol << ")" << ansi::reset;
    return sstr.str();
}


////////////////////////////////////////////////////////////////////////////////////
//  layout inspired by gawin's kool xterm color demo [1]
//  [1] https://github.com/gawin/bash-colors-256
void printColorTable( const bool foreground, const bool background )
{
    auto escapeCode = [=]( const uint8_t& id ) -> std::string
    {
        char idstr[ 4 ];
        std::snprintf( idstr, 4, "%03d", id );

        const std::string bgstr = ansi::bg( id ) + ansi::text + " " + idstr + " " + ansi::reset;
        const std::string fgstr = ansi::fg( id ) + " " + idstr + " " + ansi::reset;

        if ( ! background ) {
            return fgstr;
        }

        if ( ! foreground ) {
            return bgstr;
        }

        return bgstr + fgstr;
    };

    for ( uint8_t i = 0; i < 8; i++ ) {
        std::cout << escapeCode( i );
    }

    std::cout << std::endl;

    for ( uint8_t i = 8; i < 16; i++ ) {
        std::cout << escapeCode( i );
    }

    std::cout << std::endl;
    std::cout << std::endl;

    const size_t numSteps = 6;
    const float step = ( numSteps == 1 ) ? 255.f : ( 255.f / ( numSteps - 1 ) );

    for ( float r = 0.f; r <= 255.f; r += step )
    {
        const uint8_t r8 = uint8_t( std::round( r ) );

        for ( float g = 0.f; g <= 255.f; g += step )
        {
            const uint8_t g8 = uint8_t( std::round( g ) );

            for ( float b = 0.f; b <= 255.f; b += step )
            {
                const uint8_t b8 = uint8_t( std::round( b ) );
                const uint32_t val = uint32_t( ( r8 << 16 ) + ( g8 << 8 ) + b8 );

                std::cout << escapeCode( index::fromRgb( rgb::fromRgb32( val ) ));
            }

            std::cout << std::endl;
        }

        std::cout << std::endl;
    }

    //  NOTE(tgurdan): uint8_t causes endless loop here
    for ( uint16_t i = 232; i <= 255; i++ )
    {
        std::cout << escapeCode( uint8_t( i ) );

        if ( i % 6 == 3 ) {
            std::cout << std::endl;
        }
    }
}


////////////////////////////////////////////////////////////////////////////////
void printColorPresets()
{
    std::cout << ansi::lightRed << "light" << ansi::red << " red \n";
    std::cout << ansi::lightGreen << "light" << ansi::green << " green \n";
    std::cout << ansi::lightBlue << "light" << ansi::blue << " blue \n";
    std::cout << ansi::lightYellow << "light" << ansi::yellow << " yellow \n";

    std::cout << "\n";
    std::cout << ansi::subtleText << "subtle" << ansi::text << " text \n";
    std::cout << ansi::subtleSymbol << "subtle" << ansi::symbol << " symbol \n";

    std::cout << "\n";
    std::cout << ansi::black << "black ";
    std::cout << ansi::grey50 << "grey50 ";
    std::cout << ansi::grey100 << "grey100 ";
    std::cout << ansi::grey150 << "grey150 ";
    std::cout << ansi::grey200 << "grey200 ";
    std::cout << ansi::white << "white \n";

    std::cout << ansi::reset;
}


}   //  ::vivid::ansi


}   //  ::vivid
