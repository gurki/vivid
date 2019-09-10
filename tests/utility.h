#pragma once

#include "vivid/types.h"
#include <random>


inline float randf( const float from = 0.f, const float to = 1.f )
{
    static std::random_device rd;
    static std::mt19937 mt( rd() );

    std::uniform_real_distribution<> dist( from, to );
    return dist( mt );
};


inline int randi( const int from = 0, const int to = 255 )
{
    static std::random_device rd;
    static std::mt19937 mt( rd() );

    std::uniform_int_distribution<> dist( from, to );
    return dist( mt );
};


namespace vivid::rgb {
    inline rgb_t rand() {
        return { randf(), randf(), randf() };
    }
}


namespace vivid::rgb8 {
    inline col8_t rand() {
        return { randi(), randi(), randi() };
    }
}
