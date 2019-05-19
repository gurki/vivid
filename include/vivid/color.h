#pragma once

#include "vivid/types.h"
#include <string>

namespace vivid {


class Color
{
    public:

        enum Space {
            SpaceUndefined,
            SpaceRgb,   //  assumes sRGB for XYZ conversion
            SpaceHsl,
            SpaceHsv,
            SpaceHcl
        };

        Color() = default;        
        Color( const col_t& value, const Space = SpaceRgb );
        Color( const col8_t& rgb8 );
        Color( const uint32_t rgb32 );
        Color( const uint8_t index );
        Color( const std::string& hexOrName );

        bool valid() const { return space_ != SpaceUndefined; }
        const col_t& value() const { return value_; }
        Space space() const { return space_; }
        std::string spaceInfo() const;

        Color rgb() const;
        Color hsl() const;
        Color hsv() const;
        Color hcl() const;
        col8_t rgb8() const;
        uint32_t rgb32() const;
        uint8_t index() const;
        std::string hex() const;
        std::string name() const;

    private:

        col_t value_ = {};
        Space space_ = SpaceUndefined;
};


Color lerp( const Color&, const Color&, const float );


}   //  ::vivid
