#pragma once

#include "vivid/types.h"
#include <iostream>
#include <iomanip>


////////////////////////////////////////////////////////////////////////////////
inline std::ostream& operator << ( std::ostream& out, const tq::col_t& col ) {
    out << "col(" << std::setprecision( 2 ) << col.x << ", " << col.y << ", " << col.z << ")";
    return out;
}


////////////////////////////////////////////////////////////////////////////////
inline std::ostream& operator << ( std::ostream& out, const tq::col8_t& col ) {
    out << "rgb(" << int( col.x ) << ", " << int( col.y ) << ", " << int( col.z ) << ")";
    return out;
}
