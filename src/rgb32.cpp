#include "vivid/conversion.h"
#include <regex>
#include <sstream>

namespace tq::rgbu32 {


////////////////////////////////////////////////////////////////////////////////
uint32_t fromRGB( const col_t& rgb ) {
    return rgbu32::fromRGB888( rgb888::fromRGB( rgb ) );
}


////////////////////////////////////////////////////////////////////////////////
uint32_t fromRGB888( const colu8_t& rgb888 )
{
    uint32_t rgbu32 = 0xff000000;
    rgbu32 |= rgb888.r << 16;
    rgbu32 |= rgb888.g << 8;
    rgbu32 |= rgb888.b;

    return rgbu32;
}


////////////////////////////////////////////////////////////////////////////////
uint32_t fromHex( const std::string& hexStr )
{
    //  try hex
    std::regex re( "^#((?:[0-9a-fA-F]{3}){1,2})$" );
    std::smatch match;
    std::regex_match( hexStr, match, re );

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

    uint32_t rgbu32;
    ss >> rgbu32;

    return rgbu32;
}


}   //  ::tq::rgbu32
