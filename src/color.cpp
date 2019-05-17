#include "vivid/color.h"
#include "vivid/colortable.h"
#include "vivid/conversion.h"
#include "vivid/functions.h"
#include "vivid/stream.h"

namespace tq {


////////////////////////////////////////////////////////////////////////////////
Color::Color( const col_t& value, const Space space ) :
    value_( value ),
    space_( space )
{}


////////////////////////////////////////////////////////////////////////////////
Color::Color( const col8_t& rgb8 ) :
    value_( rgb::fromRgb8( rgb8 ) ),
    space_( SpaceRgb )
{}


////////////////////////////////////////////////////////////////////////////////
Color::Color( const uint32_t rgb32 ) :
    value_( rgb::fromRgb32( rgb32 ) ),
    space_( SpaceRgb )
{}


////////////////////////////////////////////////////////////////////////////////
Color::Color( const uint8_t index )
{
    if ( ColorTable::empty() ) {
        return;
    }

    value_ = rgb::fromIndex( index );
    space_ = SpaceRgb;
}


////////////////////////////////////////////////////////////////////////////////
Color::Color( const std::string& hexOrName )
{
    const auto rgb32 = rgb32::fromHex( hexOrName );

    if ( rgb32 ) {
        value_ = rgb::fromRgb32( rgb32 );
        space_ = SpaceRgb;
        return;
    }

    if ( const auto maybeValue = ColorTable::findName( hexOrName ) ) {
        value_ = rgb::fromIndex( maybeValue.value_or( 0 ) );
        space_ = SpaceRgb;
        return;
    }
}


////////////////////////////////////////////////////////////////////////////////
std::string Color::spaceInfo() const
{
    switch ( space_ ) {
        case SpaceRgb: return "rgb";
        case SpaceHsl: return "hsl";
        case SpaceHsv: return "hsv";
        case SpaceHcl: return "hcl";
        default: return {};
    }
}


////////////////////////////////////////////////////////////////////////////////
Color Color::rgb() const
{
    switch ( space_ )
    {
        case SpaceRgb: return Color( value_, SpaceRgb );
        case SpaceHsl: return Color( rgb::fromHsl( value_ ), SpaceRgb );
        case SpaceHsv: return Color( rgb::fromHsv( value_ ), SpaceRgb );
        case SpaceHcl: return Color( rgb::fromHcl( value_ ), SpaceRgb );
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
        case SpaceHcl: return Color( hsl::fromRgb( rgb::fromHcl( value_ ) ), SpaceHsl );
        default: return {};
    }
}


////////////////////////////////////////////////////////////////////////////////
Color Color::hsv() const
{
    switch ( space_ )
    {
        case SpaceRgb: return Color( hsv::fromRgb( value_ ), SpaceHsv );
        case SpaceHsl: return Color( hsv::fromHsl( value_ ), SpaceHsv );
        case SpaceHsv: return Color( value_, SpaceHsv );
        case SpaceHcl: return Color( hsv::fromRgb( rgb::fromHcl( value_ ) ), SpaceHsv );
        default: return {};
    }
}


////////////////////////////////////////////////////////////////////////////////
Color Color::hcl() const
{
    switch ( space_ )
    {
        case SpaceRgb: return Color( hcl::fromRgb( value_ ), SpaceHcl );
        case SpaceHsl: return Color( hcl::fromRgb( rgb::fromHsl( value_ ) ), SpaceHcl );
        case SpaceHsv: return Color( hcl::fromRgb( rgb::fromHsv( value_ ) ), SpaceHcl );
        case SpaceHcl: return Color( value_, SpaceHcl );
        default: return {};
    }
}


////////////////////////////////////////////////////////////////////////////////
col8_t Color::rgb8() const
{
    switch ( space_ )
    {
        case SpaceRgb: return rgb8::fromRgb( value_ );
        case SpaceHsl: return rgb8::fromRgb( rgb::fromHsl( value_ ) );
        case SpaceHsv: return rgb8::fromRgb( rgb::fromHsv( value_ ) );
        case SpaceHcl: return rgb8::fromRgb( rgb::fromHcl( value_ ) );
        default: return {};
    }
}


////////////////////////////////////////////////////////////////////////////////
uint32_t Color::rgb32() const
{
    switch ( space_ )
    {
        case SpaceRgb: return rgb32::fromRgb( value_ );
        case SpaceHsl: return rgb32::fromRgb( rgb::fromHsl( value_ ) );
        case SpaceHsv: return rgb32::fromRgb( rgb::fromHsv( value_ ) );
        case SpaceHcl: return rgb32::fromRgb( rgb::fromHcl( value_ ) );
        default: return {};
    }
}


////////////////////////////////////////////////////////////////////////////////
uint8_t Color::index() const
{
    switch ( space_ )
    {
        case SpaceRgb: return index::fromRgb( value_ );
        case SpaceHsl: return index::fromHsl( value_ );
        case SpaceHsv: return index::fromRgb( rgb::fromHsv( value_ ) );
        case SpaceHcl: return index::fromRgb( rgb::fromHcl( value_ ) );
        default: return {};
    }
}


////////////////////////////////////////////////////////////////////////////////
std::string Color::hex() const
{
    switch ( space_ )
    {
        case SpaceRgb: return hex::fromRgb( value_ );
        case SpaceHsl: return hex::fromRgb( rgb::fromHsl( value_ ) );
        case SpaceHsv: return hex::fromRgb( rgb::fromHsv( value_ ) );
        case SpaceHcl: return hex::fromRgb( rgb::fromHcl( value_ ) );
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
        case SpaceHcl: return name::fromRgb( rgb::fromHcl( value_ ) );
        default: return {};
    }
}


////////////////////////////////////////////////////////////////////////////////
Color lerp( const Color& c1, const Color& c2, const float t )
{
    if ( c1.space() != c2.space() ) {
        return {};
    }

    switch ( c1.space() ) {
        case Color::SpaceRgb: return Color( rgb::lerp( c1.value(), c2.value(), t ), Color::SpaceRgb );
        case Color::SpaceHsl: return Color( hsl::lerp( c1.value(), c2.value(), t ), Color::SpaceHsl );
        case Color::SpaceHsv: return Color( hsv::lerp( c1.value(), c2.value(), t ), Color::SpaceHsv );
        case Color::SpaceHcl: return Color( hcl::lerp( c1.value(), c2.value(), t ), Color::SpaceHcl );
        default: return {};
    }
}


}   //  ::tq
