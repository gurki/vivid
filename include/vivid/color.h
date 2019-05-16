#pragma once

#include "vivid/types.h"

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
            SpaceHcl
        };

        Color() = default;

        bool valid() const { return space_ != SpaceUndefined; }
        const col_t& value() const { return value_; }
        Space space() const { return space_; }
//        std::string spaceInfo() const;

//        Color rgb() const;
//        Color hsl() const;
//        Color hsv() const;
//        Color hcl() const;
//        col8_t rgb8() const;
//        uint32_t rgb32() const;
//        uint8_t index() const;
//        std::string hex() const;
//        std::string name() const;

//        static Color fromRgb( const col_t& );
//        static Color fromHsl( const col_t& );
//        static Color fromHsv( const col_t& );
//        static Color fromHcl( const col_t& );
//        static Color fromRgb8( const col8_t& );
//        static Color fromRgb32( const uint32_t );
//        static Color fromIndex( const uint8_t );
//        static Color fromHex( const std::string& );
//        static Color fromName( const std::string& );

    private:

//        Color( const col_t&, const Space );

        col_t value_ = {};
        Space space_ = SpaceUndefined;
};


//std::ostream& operator << ( std::ostream& out, const Color& col );

//Color lerp( const Color&, const Color&, const float );


}   //  ::tq
