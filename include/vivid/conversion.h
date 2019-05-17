#pragma once

#include "vivid/types.h"
#include <string>

namespace vivid {


//  xyz \in [ ( 0, 0, 0 ), ( 1, 1, 1 ) ]
namespace xyz
{
    col_t fromLab( const col_t& );
    col_t fromRgb( const col_t& );

    //  observer 2°, illuminant D65
    static const col_t xyz_ref = col_t( 0.95047f, 1.f, 1.08883f );
}


//  lab \in [ ( 0, -86.1827, -107.86 ), ( 100, 98.2343, 94.478 ) ]
namespace lab {
    col_t fromXyz( const col_t& );
    col_t fromHcl( const col_t& );
}


//  hcl \in [ ( 0, 0, -2 PI ), ( 100, 133.808, 2 PI ) ]
namespace hcl {
    col_t fromLab( const col_t& );
    col_t fromRgb( const col_t& );  //  (-)
}


//  hsv \in [0; 1]
namespace hsv {
    col_t fromHsl( const col_t& );  //  (-)
    col_t fromRgb( const col_t& );
}


//  hsl \in [0; 1]
namespace hsl {
    col_t fromIndex( const uint8_t );   //  *
    col_t fromHsv( const col_t& );      //  (-)
    col_t fromRgb( const col_t& );
}


//  rgb \in [0; 1]
namespace rgb
{
    col_t fromRgb8( const col8_t& );
    col_t fromRgb32( const uint32_t );      //  (-)
    col_t fromHsv( const col_t& );
    col_t fromHsl( const col_t& );
    col_t fromXyz( const col_t& );
    col_t fromHcl( const col_t& );          //  (-)
    col_t fromHex( const std::string& );    //  (-)
    col_t fromIndex( const uint8_t );       //  (-)
    col_t fromName( const std::string& );   //  *(-)
}


//  rgb8 \in [0;255]
namespace rgb8 {
    col8_t fromRgb( const col_t& );
    col8_t fromRgb32( const uint32_t );
    col8_t fromIndex( const uint8_t );      //  *
    col8_t fromName( const std::string& );  //  *(-)
    col8_t fromHex( const std::string& );   //  (-)
}


//  rgb32 as 0xffRRGGBB
namespace rgb32 {
    uint32_t fromRgb( const col_t& );       //  (-)
    uint32_t fromRgb8( const col8_t& );
    uint32_t fromHex( const std::string& );
}


//  ansi color index (for use in e.g. ansi escape codes)
namespace index {
    uint8_t fromRgb( const col_t& );        //  (-)
    uint8_t fromRgb8( const col8_t& );      //  *
    uint8_t fromName( const std::string& ); //  *
    uint8_t fromHsl( const col_t& );  //  (-)
    uint8_t fromHex( const std::string& );  //  (-)
}


//  hex string
namespace hex {
    std::string fromRgb( const col_t& );    //  (-)
    std::string fromRgb8( const col8_t& );
    std::string fromRgb32( const uint32_t );
    std::string fromIndex( const uint8_t ); //  *
}


//  (nearest) xterm color name
namespace name {
    std::string fromRgb( const col_t& );    //  (-)
    std::string fromIndex( const uint8_t ); //  *
}


}   //  ::vivid
