#pragma once

#include <nlohmann/json.hpp>
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
        static col_t rgb( const uint8_t id );
        static col_t hsl( const uint8_t id );

        static void printTestTable( const uint8_t numSteps = 6 );

        static bool load( const std::string& path );
        static bool empty() { return table_.empty(); }

    private:

        ColorTable() = default;
        ~ColorTable() = default;

        static nlohmann::json table_;
        static ColorTable instance_;    //  trigger population of table_
};


}   //  ::tq
