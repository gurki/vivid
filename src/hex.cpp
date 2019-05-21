#include "vivid/conversion.h"
#include "vivid/data/xterm.h"

#include <regex>
#include <sstream>
#include <iomanip>

namespace vivid::hex {


//////////////////////////////////////////////////////////////////////////////////
std::string fromIndex( const uint8_t index ) {
    return hex::fromRgb32( data::xterm.at( index ).rgb32 );
}


//////////////////////////////////////////////////////////////////////////////////
std::string fromRgb( const rgb_t& rgb ) {
    return hex::fromRgb8( rgb8::fromRgb( rgb ) );
}


//////////////////////////////////////////////////////////////////////////////////
std::string fromRgb8( const col8_t& rgb8 ) {
    std::stringstream ss;
    ss << "#";
    ss << std::hex << std::setw( 2 ) << std::setfill( '0' ) << int( rgb8.x );
    ss << std::hex << std::setw( 2 ) << std::setfill( '0' ) << int( rgb8.y );
    ss << std::hex << std::setw( 2 ) << std::setfill( '0' ) << int( rgb8.z );
    return ss.str();
}


//////////////////////////////////////////////////////////////////////////////////
std::string fromRgb32( const uint32_t rgb32 ) {
    return hex::fromRgb8( rgb8::fromRgb32( rgb32 ) );
}


}   //  ::vivid::hex
