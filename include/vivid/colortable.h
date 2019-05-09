#pragma once

#include <nlohmann/json.hpp>
#include <optional>
#include "vivid/types.h"

//  c.f.
//    https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
//    https://jonasjacek.github.io/colors/


namespace tq {


//  256 indexed ansi colors including names and various representations
class ColorTable
{
    public:

        static std::string hex( const uint8_t id );
        static std::string name( const uint8_t id );
        static col_t hsl( const uint8_t id );
        static col_t rgb( const uint8_t id );
        static colu8_t rgb888( const uint8_t id );

        static std::optional<uint8_t> findRGBu32( const uint32_t rgbu32 );

        static void printTestTable(
            const bool foreground = true,
            const bool background = true
        );

        static void initialize();
        static bool load( const std::string& path );
        static bool empty() { return table_.empty(); }

    private:

        ColorTable() = default;
        ~ColorTable() = default;

        static std::unordered_map<uint32_t, uint8_t> lookup_;   //  RGBu32 -> id
        static nlohmann::json table_;
        static ColorTable instance_;    //  trigger population of table_
};


}   //  ::tq
