#pragma once

#include "vivid/types.h"
#include <nlohmann/json.hpp>
#include <optional>

//  c.f.
//    [3] https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
//    [8] https://jonasjacek.github.io/colors/


namespace vivid {


//  256 indexed ansi colors including names and various representations
class ColorTable
{
    public:

        static const std::unordered_map<uint32_t, uint8_t>& lookup() { return lookup_; }
        static const nlohmann::json& table() { return table_; }

        static std::string hex( const uint8_t id );
        static std::string name( const uint8_t id );
        static col_t hsl( const uint8_t id );
        static col8_t rgb8( const uint8_t id );

        static std::optional<uint8_t> findRgb32( const uint32_t rgb32 );
        static std::optional<uint8_t> findName( const std::string& name );

        static bool load( const std::string& path );
        static bool empty() { return table_.empty(); }

    private:

        ColorTable() = default;
        ~ColorTable() = default;

        static std::unordered_map<uint32_t, uint8_t> lookup_;   //  rgb32 -> index
        static nlohmann::json table_;
        static ColorTable instance_;
};


void printColorTable(
    const bool foreground = true,
    const bool background = true
);


}   //  ::vivid
