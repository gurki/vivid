#pragma once

#include "vivid/types.h"
#include "vivid/stream.h"

#include <string>
#include <iostream>
#include <iomanip>

namespace tq {


class Color
{
    public:

        enum Space {
            SpaceUndefined,
            SpaceRgb,
            SpaceHsl,
            SpaceHsv,
            SpaceXyz,
            SpaceLab,
            SpaceHcl
        };

        Color() = default;

        bool valid() const { return space_ != SpaceUndefined; }
        const col_t& value() const { return value_; }
        Space space() const { return space_; }
        std::string spaceInfo() const;

        Color hsl() const;
        std::string name() const;

        static Color fromRgb( const col_t& );
        static Color lerp( const Color&, const Color&, const float );

    private:

        Color( const col_t&, const Space );

        col_t value_ = {};
        Space space_ = SpaceUndefined;
};


std::ostream& operator << ( std::ostream& out, const Color& col );


}   //  ::tq
