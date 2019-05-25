#pragma once

#include "vivid/color.h"
#include "vivid/conversion.h"
#include "vivid/utility.h"

#include <string>
#include <sstream>
#include <iomanip>


namespace vivid::ansi
{
    inline std::string fg( const uint8_t index ) {
        return "\x1b[38;5;" + std::to_string( index ) + "m";
    }

    inline std::string bg( const uint8_t index ) {
        return "\x1b[48;5;" + std::to_string( index ) + "m";
    }

    inline std::string fg( const Color& col ) {
        return "\x1b[38;5;" + std::to_string( col.index() ) + "m";
    }

    inline std::string bg( const Color& col ) {
        return "\x1b[48;5;" + std::to_string( col.index() ) + "m";
    }

    static const std::string reset = "\x1b[0m";

    static const auto black = ansi::fg( 0 );
    static const auto white = ansi::fg( 15 );

    static const auto red = ansi::fg( 196 );
    static const auto green = ansi::fg( 40 );
    static const auto blue = ansi::fg( 39 );
    static const auto yellow = ansi::fg( 220 );

    static const auto lightRed = ansi::fg( 203 );
    static const auto lightGreen = ansi::fg( 83 );
    static const auto lightBlue = ansi::fg( 81 );
    static const auto lightYellow = ansi::fg( 221 );

    static const auto text = ansi::fg( 254 );
    static const auto subtleText = ansi::fg( 242 );
    static const auto symbol = ansi::fg( 246 );
    static const auto subtleSymbol = ansi::fg( 238 );

    static const auto grey50 = ansi::fg( 236 );
    static const auto grey100 = ansi::fg( 241 );
    static const auto grey150 = ansi::fg( 246 );
    static const auto grey200 = ansi::fg( 251 );
}


namespace vivid::html
{
    inline std::string fg( const std::string& hex ) {
        return "<span style='color:" + hex + "'>";
    }

    inline std::string bg( const std::string& hex ) {
        return "<span style='background-color:" + hex + "'>";
    }

    inline std::string fg( const col8_t& rgb8 )
    {
        return (
            "<span style='color:rgb(" +
            std::to_string( rgb8.x ) + "," +
            std::to_string( rgb8.y ) + "," +
            std::to_string( rgb8.z ) + ")'>"
        );
    }

    inline std::string bg( const col8_t& rgb8 )
    {
        return (
            "<span style='background-color:rgb(" +
            std::to_string( rgb8.x ) + "," +
            std::to_string( rgb8.y ) + "," +
            std::to_string( rgb8.z ) + ")'>"
        );
    }

    inline std::string fg( const Color& col ) {
        return fg( col.rgb8() );
    }

    inline std::string bg( const Color& col ) {
        return bg( col.rgb8() );
    }

    static const std::string close = "</span>";
}
