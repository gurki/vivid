#include "vivid/functions.h"
#include "vivid/conversion.h"
#include "vivid/stream.h"
#include "vivid/encoding.h"
#include "vivid/colormap.h"

#include <glm/glm.hpp>
#include <glm/common.hpp>           //  clamp
#include <glm/gtc/constants.hpp>    //  pi
#include <glm/gtx/string_cast.hpp>

#include <iostream>
#include <sstream>


namespace vivid {


////////////////////////////////////////////////////////////////////////////////////
//  layout inspired by gawin's kool xterm color demo
//  [7] https://github.com/gawin/bash-colors-256
void printColorTable( const bool foreground, const bool background )
{
    std::cout << std::endl;

    auto escapeCode = [=]( const uint8_t& id ) -> std::string
    {
        char idstr[ 4 ];
        std::sprintf( idstr, "%03d", id );

        const std::string bgstr = vivid::ansi::bg( id ) + " " + idstr + " " + vivid::ansi::reset;
        const std::string fgstr = vivid::ansi::fg( id ) + " " + idstr + " " + vivid::ansi::reset;

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

    std::cout << std::endl << std::endl;
}


namespace rgb {


////////////////////////////////////////////////////////////////////////////////
// input 0..255 for rainbow colors!
rgb_t rainbow( const uint8_t k )
{
    rgb_t col;

    if ( k < 42 ) {
        col.x = 255;
        col.y = float( k * 6 );
        col.z = 0;
    } else if ( k < 2 * 42 ) {
        col.x = float( 42 - ( k - 42 ) ) * 6;
        col.y = 255;
        col.z = 0;
    } else if ( k < 3 * 42 ) {
        col.x = 0;
        col.y = 255;
        col.z = float( k - 2 * 42 ) * 6;
    } else if ( k < 4 * 42 ) {
        col.x = 0;
        col.y = ( 42 - float( k - 3 * 42 ) ) * 6;
        col.z = 255;
    } else if ( k < 5 * 42 ) {
        col.x = float( k - 4 * 42 ) * 6;
        col.y = 0;
        col.z = 255;
    } else if ( k < 6 * 42 ) {
        col.x = 255;
        col.y = 0;
        col.z = ( 42 - float( k - 5 * 42 ) ) * 6;
    } else {
        col.x = 255;
        col.y = 0;
        col.z = 0;
    }

    return static_cast<rgb_t>( col / 255.0f );
}


////////////////////////////////////////////////////////////////////////////////
rgb_t saturate( const rgb_t& rgb )
{
    auto res = rgb;

    res.x = glm::clamp( rgb.x, 0.f, 1.f );
    res.y = glm::clamp( rgb.y, 0.f, 1.f );
    res.z = glm::clamp( rgb.z, 0.f, 1.f );

    return res;
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


}   //  ::vivid::rgb


namespace srgb {


////////////////////////////////////////////////////////////////////////////////
float compound( const float k )
{
    if ( k <= 0.00304f ) {
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

    return std::powf( ( k + 0.055f ) / 1.055f, 2.4f );
}


}   //   ::vivid::srgb


namespace hsl {

////////////////////////////////////////////////////////////////////////////////
rgb_t rainbow( const uint8_t k, const float s, const float l ) {
    const float t = k / 256.f;
    return { t, s, l };
}

}   //  ::vivid::hsl


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
        ss << vivid::ansi::fg( id ) << text[ i ];
    }

    ss << vivid::ansi::reset;
    return ss.str();
}

}   //  ::vivid::ansi


}   //  ::vivid
