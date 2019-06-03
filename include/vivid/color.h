#pragma once

#include "vivid/types.h"
#include <string>

namespace vivid {


class Color
{
    public:

        enum class Space {
            Undefined,
            Rgb,    //  assumes sRGB, wording for confusion-free high-level API
            Hsl,
            Hsv,
            Lch
        };

        Color() = default;        
        Color( const rgb_t& rgb );
        Color( const hsl_t& hsl );
        Color( const hsv_t& hsv );
        Color( const lch_t& lch );
        Color( const col8_t& rgb8 );
        Color( const uint32_t rgb32 );
        Color( const uint8_t index );
        Color( const std::string& hexOrName );
        Color( const col_t& value, const Space );
        Color( const uint8_t r, const uint8_t g, const uint8_t b );


        bool valid() const;
        const col_t& value() const { return value_; }
        Space space() const { return space_; }
        std::string info() const;
        std::string quickInfo() const;
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
        Color saturated() const;

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

        Space space_ = Space::Undefined;
};




}   //  ::vivid
