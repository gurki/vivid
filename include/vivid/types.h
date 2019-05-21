#pragma once

#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/component_wise.hpp>

namespace vivid {


using col_t = glm::vec<3, float>;
using col8_t = glm::vec<3, uint8_t>;

struct lrgb_t;
struct srgb_t;


struct rgb_t : public col_t
{
    rgb_t() = default;
    rgb_t( const float x, const float y, const float z ) : col_t( x, y, z ) {}
    rgb_t( const srgb_t& srgb );    //  implicit cast
    rgb_t( const lrgb_t& lrgb );    //  implicit cast

    explicit rgb_t( const col_t& col ) : col_t( col ) {}
};


struct hsl_t : public col_t
{
    hsl_t() = default;
    hsl_t( const float x, const float y, const float z ) : col_t( x, y, z ) {}

    explicit hsl_t( const col_t& col ) : col_t( col ) {}
};


struct hsv_t : public col_t
{
    hsv_t() = default;
    hsv_t( const float x, const float y, const float z ) : col_t( x, y, z ) {}

    explicit hsv_t( const col_t& col ) : col_t( col ) {}
};


struct lch_t : public col_t
{
    lch_t() = default;
    lch_t( const float x, const float y, const float z ) : col_t( x, y, z ) {}

    explicit lch_t( const col_t& col ) : col_t( col ) {}
};


struct srgb_t : public col_t
{
    srgb_t() = default;
    srgb_t( const float x, const float y, const float z ) : col_t( x, y, z ) {}
    srgb_t( const rgb_t& rgb ) : col_t( rgb ) {}    //  implicit cast

    explicit srgb_t( const col_t& col ) : col_t( col ) {}
};


struct lrgb_t : public col_t
{
    lrgb_t() = default;
    lrgb_t( const float x, const float y, const float z ) : col_t( x, y, z ) {}
    lrgb_t( const rgb_t& rgb ) : col_t( rgb ) {}    //  implicit cast

    explicit lrgb_t( const col_t& col ) : col_t( col ) {}
};


struct lab_t : public col_t
{
    lab_t() = default;
    lab_t( const float x, const float y, const float z ) : col_t( x, y, z ) {}

    explicit lab_t( const col_t& col ) : col_t( col ) {}
};


struct xyz_t : public col_t
{
    xyz_t() = default;
    xyz_t( const float x, const float y, const float z ) : col_t( x, y, z ) {}

    explicit xyz_t( const col_t& col ) : col_t( col ) {}
};


struct adobe_t : public col_t
{
    adobe_t() = default;
    adobe_t( const float x, const float y, const float z ) : col_t( x, y, z ) {}

    explicit adobe_t( const col_t& col ) : col_t( col ) {}
};


rgb_t::rgb_t( const srgb_t& srgb ) : col_t( srgb ) {}
rgb_t::rgb_t( const lrgb_t& lrgb ) : col_t( lrgb ) {}


inline bool fuzzyEqual( const col_t& c1, const col_t& c2 ) {
    //  compares to ~1/255th
    return glm::all( glm::lessThan( glm::abs( c1 - c2 ), glm::vec3( 0.004f ) ));
}


inline bool fuzzyHueEqual( const col_t& c1, const col_t& c2 )
{
    //  compares to ~1/255th and wraps hue

    const auto delta = glm::abs( c1 - c2 );

    return (
        ( delta.x < 0.004f || delta.x > 0.096f ) &&
        ( delta.y < 0.004f ) &&
        ( delta.z < 0.004f )
    );
}


}   //  ::vivid
