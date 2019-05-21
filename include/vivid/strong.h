#pragma once

#include <glm/vec3.hpp>
#include <iostream>

namespace vivid {


using col_t = glm::vec<3, float>;
using col8_t = glm::vec<3, uint8_t>;

struct rgb_t;
struct lrgb_t;
struct srgb_t;
struct hsl_t;
struct lch_t;

struct rgb_t : public col_t
{
    rgb_t( const float x, const float y, const float z );
    rgb_t( const srgb_t& );                     //  cast srgb -> rgb
    rgb_t( const lrgb_t& );                     //  cast lrgb -> rgb

    explicit rgb_t( const hsl_t& );             //  convert hsl -> rgb
    private: explicit rgb_t( const col_t& );    //  copy col -> rgb

    friend rgb_t lerp( const rgb_t& rgb1, const rgb_t& rgb2, const float t );
};

struct srgb_t : public col_t
{
    srgb_t( const float x, const float y, const float z );
    srgb_t( const rgb_t& );                     //  cast; this is for convenience and assumes srgb as default rgb working space

    explicit srgb_t( const lrgb_t& );           //  convert
    private: explicit srgb_t( const col_t& );   //  copy
};

struct lrgb_t : public col_t
{
    lrgb_t( const float x, const float y, const float z );

    explicit lrgb_t( const rgb_t& );                //  cast
    explicit lrgb_t( const srgb_t& );               //  convert
    private: explicit lrgb_t( const col_t& col );   //  copy
};

struct hsl_t : public col_t
{
    hsl_t( const float x, const float y, const float z );

    explicit hsl_t( const rgb_t& );             //  convert
    private: explicit hsl_t( const col_t& );    //  copy

    friend hsl_t lerp( const hsl_t& hsl1, const hsl_t& hsl2, const float t );
};

struct lch_t : public col_t
{
    lch_t( const float x, const float y, const float z );

    explicit lch_t( const rgb_t& );             //  convert; assumes srgb
    explicit lch_t( const lrgb_t& );            //  convert
    explicit lch_t( const srgb_t& );            //  convert
    explicit lch_t( const hsl_t& );             //  convert
    private: explicit lch_t( const col_t& );    //  copy

    friend lch_t lerp( const lch_t& lch1, const lch_t& lch2, const float t );
};


}   //  ::vivid
