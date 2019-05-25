#include "vivid/conversion.h"
#include <regex>
#include <sstream>
#include <iostream>

namespace vivid::rgb32 {


////////////////////////////////////////////////////////////////////////////////
uint32_t fromRgb( const rgb_t& rgb ) {
    return rgb32::fromRgb8( rgb8::fromRgb( rgb ) );
}


////////////////////////////////////////////////////////////////////////////////
uint32_t fromRgb8( const col8_t& rgb8 )
{
    uint32_t rgb32 = 0xff000000;
    rgb32 |= uint32_t( rgb8.r << 16 );
    rgb32 |= uint32_t( rgb8.g << 8 );
    rgb32 |= rgb8.b;

    return rgb32;
}


////////////////////////////////////////////////////////////////////////////////
uint32_t fromHex( const std::string& hexStr )
{
    //  try hex

    std::regex re( "^#((?:[0-9a-fA-F]{3}){1,2})$" );
    std::smatch match;
    std::regex_match( hexStr, match, re );

    if ( match.empty() ) {
        return 0;
    }

    //  parse hex

    std::stringstream ss;
    const std::string& hexstr = match[ 1 ];

    ss << std::hex;

    if ( hexstr.size() == 3 )  {
        //  unpack 3-digit hex
        for ( const auto& c : hexstr ) {
            ss << c << c;
        }
    } else {
        ss << hexstr;
    }

    uint32_t rgb32;
    ss >> rgb32;
    rgb32 |= 0xff000000;

    return rgb32;
}


}   //  ::vivid::rgb32
