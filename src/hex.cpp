#include "vivid/conversion.h"
#include <regex>

namespace tq::hex {


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
