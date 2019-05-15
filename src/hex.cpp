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
std::string fromRGB( const col_t& rgb ) {
    return hex::fromRGB888( rgb888::fromRGB( rgb ) );
}


//////////////////////////////////////////////////////////////////////////////////
std::string fromRGB888( const colu8_t& rgb888 ) {
    std::stringstream ss;
    ss << "#" << std::hex << int( rgb888.x ) << int( rgb888.y ) << int( rgb888.z );
    return ss.str();
}


//////////////////////////////////////////////////////////////////////////////////
//fromHex( const std::string& hexOrName )
//{
//    //  try hex
//    std::regex re( "^#((?:[0-9a-fA-F]{3}){1,2})$" );
//    std::smatch match;
//    std::regex_match( hexOrName, match, re );

//    //  parse hex

//    std::stringstream ss;
//    const std::string& hexstr = match[ 1 ];

//    ss << std::hex;

//    if ( hexstr.size() == 3 )  {
//        //  unpack 3-digit hex
//        for ( const auto& c : hexstr ) {
//            ss << c << c;
//        }
//    } else {
//        ss << hexstr;
//    }

//    uint32_t rgba;
//    ss >> rgba;

//    id_ = fromRGBA( rgba );
//}


}   //  ::tq::hex
