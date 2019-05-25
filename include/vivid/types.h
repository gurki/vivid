#pragma once

#include <glm/vec3.hpp>

namespace vivid {


using col_t = glm::vec<3, float>;
using col8_t = glm::vec<3, uint8_t>;

//  rgb8 (col8_t) \in [0;255]
//  rgb32 (uint32_t) as 0xffRRGGBB
//  ansi color index (uint8_t) (for use in e.g. ansi escape codes)
//  hex string (std::string)
//  xterm color name (std::string)

struct lrgb_t;
struct srgb_t;
struct adobe_t;


////////////////////////////////////////////////////////////////////////////////
//  main color spaces

//  rgb \in [0; 1]
struct rgb_t : public col_t
{
    rgb_t() = default;
    rgb_t( const float x, const float y, const float z ) : col_t( x, y, z ) {}
    rgb_t( const srgb_t& srgb );    //  implicit cast
    rgb_t( const lrgb_t& lrgb );    //  implicit cast
    rgb_t( const adobe_t& adobe );  //  implicit cast

    explicit rgb_t( const col_t& col ) : col_t( col ) {}
};


//  hsl \in [0; 1]
struct hsl_t : public col_t
{
    hsl_t() = default;
    hsl_t( const float x, const float y, const float z ) : col_t( x, y, z ) {}

    explicit hsl_t( const col_t& col ) : col_t( col ) {}
};


//  hsv \in [0; 1]
struct hsv_t : public col_t
{
    hsv_t() = default;
    hsv_t( const float x, const float y, const float z ) : col_t( x, y, z ) {}

    explicit hsv_t( const col_t& col ) : col_t( col ) {}
};


//  CIE L*C*h(ab) \in [ (0, 0, 0); (100, 140, 360) ]
struct lch_t : public col_t
{
    lch_t() = default;
    lch_t( const float x, const float y, const float z ) : col_t( x, y, z ) {}

    explicit lch_t( const col_t& col ) : col_t( col ) {}
};


//  CIE L*a*b* \in [ (0, -86.1827, -107.86); (100, 98.2343, 94.478) ]
struct lab_t : public col_t
{
    lab_t() = default;
    lab_t( const float x, const float y, const float z ) : col_t( x, y, z ) {}

    explicit lab_t( const col_t& col ) : col_t( col ) {}
};


//  CIE XYZ \in [ (0, 0, 0), profiles::XYZ_d65 ]
struct xyz_t : public col_t
{
    xyz_t() = default;
    xyz_t( const float x, const float y, const float z ) : col_t( x, y, z ) {}

    explicit xyz_t( const col_t& col ) : col_t( col ) {}
};


////////////////////////////////////////////////////////////////////////////////
//  derived rgb working spaces

struct srgb_t : public rgb_t
{
    srgb_t() = default;
    srgb_t( const float x, const float y, const float z ) : rgb_t( x, y, z ) {}
    srgb_t( const rgb_t& rgb ) : rgb_t( rgb ) {}    //  implicit cast

    explicit srgb_t( const col_t& col ) : rgb_t( col ) {}
};


//  linear rgb
struct lrgb_t : public rgb_t
{
    lrgb_t() = default;
    lrgb_t( const float x, const float y, const float z ) : rgb_t( x, y, z ) {}
    lrgb_t( const rgb_t& rgb ) : rgb_t( rgb ) {}    //  implicit cast

    explicit lrgb_t( const col_t& col ) : rgb_t( col ) {}
};


//  adobe rgb (1998)
struct adobe_t : public rgb_t
{
    adobe_t() = default;
    adobe_t( const float x, const float y, const float z ) : rgb_t( x, y, z ) {}
    adobe_t( const rgb_t& rgb ) : rgb_t( rgb ) {}    //  implicit cast

    explicit adobe_t( const col_t& col ) : rgb_t( col ) {}
};


//  color operators

bool fuzzyEqual( const col_t& c1, const col_t& c2 );
bool fuzzyHueEqual( const col_t& c1, const col_t& c2 );


}   //  ::vivid
