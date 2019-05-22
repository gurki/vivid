#pragma once

#include "vivid/types.h"
#include "vivid/color.h"

#include <glm/gtx/string_cast.hpp>

#include <iostream>
#include <iomanip>


////////////////////////////////////////////////////////////////////////////////
inline std::ostream& operator << ( std::ostream& out, const glm::vec3& vec ) {
    out << glm::to_string( vec );
    return out;
}


////////////////////////////////////////////////////////////////////////////////
inline std::ostream& operator << ( std::ostream& out, const glm::mat3& mat ) {
    out << glm::to_string( mat );
    return out;
}


////////////////////////////////////////////////////////////////////////////////
inline std::ostream& operator << ( std::ostream& out, const vivid::rgb_t& col ) {
    out << "rgb(" << std::setprecision( 3 ) << col.x << ", " << col.y << ", " << col.z << ")";
    return out;
}


////////////////////////////////////////////////////////////////////////////////
inline std::ostream& operator << ( std::ostream& out, const vivid::srgb_t& col ) {
    out << "srgb(" << std::setprecision( 3 ) << col.x << ", " << col.y << ", " << col.z << ")";
    return out;
}


////////////////////////////////////////////////////////////////////////////////
inline std::ostream& operator << ( std::ostream& out, const vivid::lrgb_t& col ) {
    out << "lrgb(" << std::setprecision( 3 ) << col.x << ", " << col.y << ", " << col.z << ")";
    return out;
}


////////////////////////////////////////////////////////////////////////////////
inline std::ostream& operator << ( std::ostream& out, const vivid::adobe_t& col ) {
    out << "adobe(" << std::setprecision( 3 ) << col.x << ", " << col.y << ", " << col.z << ")";
    return out;
}


////////////////////////////////////////////////////////////////////////////////
inline std::ostream& operator << ( std::ostream& out, const vivid::hsl_t& col ) {
    out << "hsl(" << std::setprecision( 3 ) << col.x << ", " << col.y << ", " << col.z << ")";
    return out;
}


////////////////////////////////////////////////////////////////////////////////
inline std::ostream& operator << ( std::ostream& out, const vivid::hsv_t& col ) {
    out << "hsv(" << std::setprecision( 3 ) << col.x << ", " << col.y << ", " << col.z << ")";
    return out;
}


////////////////////////////////////////////////////////////////////////////////
inline std::ostream& operator << ( std::ostream& out, const vivid::lab_t& col ) {
    out << "lab(" << col.x << ", " << col.y << ", " << col.z << ")";
    return out;
}


////////////////////////////////////////////////////////////////////////////////
inline std::ostream& operator << ( std::ostream& out, const vivid::lch_t& col ) {
    out << "lch(" << col.x << ", " << col.y << ", " << col.z << ")";
    return out;
}


////////////////////////////////////////////////////////////////////////////////
inline std::ostream& operator << ( std::ostream& out, const vivid::xyz_t& col ) {
    out << "xyz(" << col.x << ", " << col.y << ", " << col.z << ")";
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
