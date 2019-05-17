#pragma once

#include "vivid/types.h"
#include <QColor>
#include <random>


inline float randf( const float from = 0.f, const float to = 1.f )
{
    static std::random_device rd;
    static std::mt19937 mt( rd() );

    std::uniform_real_distribution dist( from, to );
    return dist( mt );
};


inline int randi( const int from = 0, const int to = 255 )
{
    static std::random_device rd;
    static std::mt19937 mt( rd() );

    std::uniform_int_distribution dist( from, to );
    return dist( mt );
};


namespace tq::rgb {
    inline col_t rand() {
        return { randf(), randf(), randf() };
    }
}


namespace tq::rgb8 {
    inline col8_t rand() {
        return { randi(), randi(), randi() };
    }
}


namespace tq::rgb {
    inline col_t fromQt( const QColor& qcol ) {
        return { qcol.redF(), qcol.greenF(), qcol.blueF() };
    }
}
