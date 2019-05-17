#pragma once

#include "vivid/types.h"
#include "vivid/color.h"

#include <iostream>
#include <iomanip>


////////////////////////////////////////////////////////////////////////////////
inline std::ostream& operator << ( std::ostream& out, const vivid::col_t& col ) {
    out << "col(" << std::setprecision( 3 ) << col.x << ", " << col.y << ", " << col.z << ")";
    return out;
}


////////////////////////////////////////////////////////////////////////////////
inline std::ostream& operator << ( std::ostream& out, const vivid::col8_t& col ) {
    out << "rgb(" << int( col.x ) << ", " << int( col.y ) << ", " << int( col.z ) << ")";
    return out;
}


////////////////////////////////////////////////////////////////////////////////
inline std::ostream& operator << ( std::ostream& out, const vivid::Color& col )
{
    out << col.spaceInfo() << "(";
    out << std::setprecision( 3 ) << col.value().x << ", " << col.value().y << ", " << col.value().z;
    out << ")";

    return out;
}
