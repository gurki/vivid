#include "vivid/conversion.h"
#include "vivid/colortable.h"

#include <regex>
#include <sstream>

namespace tq::hex {


//////////////////////////////////////////////////////////////////////////////////
std::string fromIndex( const uint8_t index ) {
    return ColorTable::hex( index );
}


//////////////////////////////////////////////////////////////////////////////////
std::string fromRgb( const col_t& rgb ) {
    return hex::fromRgb8( rgb8::fromRgb( rgb ) );
}


//////////////////////////////////////////////////////////////////////////////////
std::string fromRgb8( const col8_t& rgb8 ) {
    std::stringstream ss;
    ss << "#" << std::hex << int( rgb8.x ) << int( rgb8.y ) << int( rgb8.z );
    return ss.str();
}


//////////////////////////////////////////////////////////////////////////////////
std::string fromRgb32( const uint32_t rgb32 ) {
    return hex::fromRgb8( rgb8::fromRgb32( rgb32 ) );
}


}   //  ::tq::hex
