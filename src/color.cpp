#include "vivid/color.h"
#include "vivid/conversion.h"
#include "vivid/functions.h"

#include <glm/common.hpp>

namespace tq {


////////////////////////////////////////////////////////////////////////////////
Color::Color( const col_t& col, const Space space ) :
    value_( col ),
    space_( space )
{}


////////////////////////////////////////////////////////////////////////////////
std::string Color::spaceInfo() const
{
    switch ( space_ ) {
        case SpaceRgb: return "rgb";
        case SpaceHsl: return "hsl";
        case SpaceHsv: return "hsv";
        case SpaceXyz: return "xyz";
        case SpaceLab: return "lab";
        case SpaceHcl: return "hcl";
        default: return {};
    }
}


////////////////////////////////////////////////////////////////////////////////
Color Color::hsl() const
{
    switch ( space_ )
    {
        case SpaceRgb: return Color( hsl::fromRgb( value_ ), SpaceHsl );
        case SpaceHsl: return Color( value_, SpaceHsl );
        case SpaceHsv: return Color( hsl::fromHsv( value_ ), SpaceHsl );
        case SpaceXyz: return Color( hsl::fromRgb( rgb::fromXyz( value_ ) ), SpaceHsl );
        case SpaceLab: return Color( hsl::fromRgb( rgb::fromXyz( xyz::fromLab( value_ ) )), SpaceHsl );
        case SpaceHcl: return Color( hsl::fromRgb( rgb::fromHcl( value_ ) ), SpaceHsl );
        default: return {};
    }
}


////////////////////////////////////////////////////////////////////////////////
std::string Color::name() const
{
    switch ( space_ )
    {
        case SpaceRgb: return name::fromRgb( value_ );
        case SpaceHsl: return name::fromRgb( rgb::fromHsl( value_ ) );
        case SpaceHsv: return name::fromRgb( rgb::fromHsv( value_ ) );
        case SpaceXyz: return name::fromRgb( rgb::fromXyz( value_ ) );
        case SpaceLab: return name::fromRgb( rgb::fromXyz( xyz::fromLab( value_ ) ));
        case SpaceHcl: return name::fromRgb( rgb::fromHcl( value_ ) );
        default: return {};
    }
}


////////////////////////////////////////////////////////////////////////////////
Color Color::fromRgb( const col_t& rgb ) {
    return Color( rgb, SpaceRgb );
}


////////////////////////////////////////////////////////////////////////////////
Color Color::lerp( const Color& c1, const Color& c2, const float t )
{
    if ( c1.space() != c2.space() ) {
        return {};
    }

    switch ( c1.space() ) {
        case SpaceRgb: return Color( tq::rgb::lerp( c1.value(), c2.value(), t ), SpaceRgb );
        case SpaceHsl: return Color( tq::hsl::lerp( c1.value(), c2.value(), t ), SpaceHsl );
        case SpaceHsv: return Color( tq::hsv::lerp( c1.value(), c2.value(), t ), SpaceHsv );
        case SpaceXyz: return {};
        case SpaceLab: return {};
        case SpaceHcl: return Color( tq::hcl::lerp( c1.value(), c2.value(), t ), SpaceHcl );
        default: return {};
    }
}


////////////////////////////////////////////////////////////////////////////////
std::ostream& operator << ( std::ostream& out, const Color& col )
{
    out << col.spaceInfo() << "(";
    out << std::setprecision( 3 ) << col.value().x << ", " << col.value().y << ", " << col.value().z;
    out << ")";

    return out;
}


}   //  ::tq
