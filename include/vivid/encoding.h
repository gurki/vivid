#pragma once

#include "vivid/color.h"
#include "vivid/conversion.h"
#include "vivid/functions.h"

#include <string>
#include <sstream>


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
    static const auto grey100 = ansi::fg( 241 );
    static const auto grey150 = ansi::fg( 246 );

    inline std::string colorize( const col_t& col, const std::string& label )
    {
        std::stringstream sstr;
        sstr << grey100 << label << grey150 << "(" << ansi::reset;
        sstr << col.x << grey150 << ", " << ansi::reset;
        sstr << col.y << grey150 << ", " << ansi::reset;
        sstr << col.z << grey150 << ")" << ansi::reset;
        return sstr.str();
    }
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
            std::to_string( rgb8.x ) + ", " +
            std::to_string( rgb8.y ) + ", " +
            std::to_string( rgb8.z ) + ")'>"
        );
    }

    inline std::string bg( const col8_t& rgb8 )
    {
        return (
            "<span style='background-color:rgb(" +
            std::to_string( rgb8.x ) + ", " +
            std::to_string( rgb8.y ) + ", " +
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
