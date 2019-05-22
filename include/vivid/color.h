#pragma once

#include "vivid/types.h"
#include <string>

namespace vivid {


class Color
{
    public:

        enum Space {
            SpaceUndefined,
            SpaceRgb,   //  assumes sRGB, wording for confusion-free high-level API
            SpaceHsl,
            SpaceHsv,
            SpaceLch
        };

        Color() = default;        
        Color( const srgb_t& srgb );
        Color( const hsl_t& hsl );
        Color( const hsv_t& hsv );
        Color( const lch_t& lch );
        Color( const col8_t& rgb8 );
        Color( const uint32_t rgb32 );
        Color( const uint8_t index );
        Color( const std::string& hexOrName );
        Color( const col_t& value, const Space );

        bool valid() const { return space_ != SpaceUndefined; }
        const col_t& value() const { return value_; }
        Space space() const { return space_; }
        std::string spaceInfo() const;

        Color rgb() const;
        Color hsl() const;
        Color hsv() const;
        Color lch() const;
        col8_t rgb8() const;
        uint32_t rgb32() const;
        uint8_t index() const;
        std::string hex() const;
        const std::string& name() const;

        //  implemented in src/interpolation.cpp
        friend Color lerp( const Color&, const Color&, const float );

    private:

        union {
            col_t value_;
            srgb_t srgb_;
            hsv_t hsv_;
            hsl_t hsl_;
            lch_t lch_;
        };

        Space space_ = SpaceUndefined;
};




}   //  ::vivid
