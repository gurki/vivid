#pragma once

#include "vivid/types.h"
#include "vivid/conversion.h"

#include <glm/glm.hpp>
#include <glm/common.hpp>
#include <glm/gtc/epsilon.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/component_wise.hpp>

#include <iostream>

namespace vivid {


using col_t = glm::vec<3, float>;
using col8_t = glm::vec<3, uint8_t>;

//struct rgb_t;
struct hsl_t : public col_t { using col_t::col_t; };
struct lch_t : public col_t { using col_t::col_t; };

struct rgb_t : public col_t
{
    using col_t::col_t;

    rgb_t( const col_t& col ) {
        *this = col;
    }

    explicit rgb_t( const hsl_t& hsl ) {
        *this = rgb_t( rgb::fromHsl( hsl ) );
    }

    explicit rgb_t( const lch_t& lch ) {
        *this = rgb_t( rgb::fromLch( lch ) );
    }
};


inline rgb_t lerp( const rgb_t& rgb1, const rgb_t& rgb2, const float t ) {
    std::cout << "lerp rgb" << std::endl;
    return rgb1 + ( rgb2 - rgb1 ) * t; //glm::mix( rgb1, rgb2, t );
}

//inline hsl_t lerp( const hsl_t& rgb1, const hsl_t& rgb2, const float t ) {
//    std::cout << "lerp hsl" << std::endl;
//    return rgb1 + ( rgb2 - rgb1 ) * t; // glm::mix( rgb1, rgb2, t );
//}


}   //  ::vivid
