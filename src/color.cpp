#include "vivid/color.h"
#include "vivid/conversion.h"
#include "vivid/functions.h"
#include "vivid/interpolation.h"
#include "vivid/stream.h"
#include "vivid/data/xterm.h"

namespace vivid {


////////////////////////////////////////////////////////////////////////////////
Color::Color( const col_t& value, const Space space ) :
    value_( value ),
    space_( space )
{}


////////////////////////////////////////////////////////////////////////////////
Color::Color( const col8_t& rgb8 ) :
    srgb_( rgb::fromRgb8( rgb8 ) ),
    space_( SpaceRgb )
{}


////////////////////////////////////////////////////////////////////////////////
Color::Color( const uint32_t rgb32 ) :
    srgb_( rgb::fromRgb32( rgb32 ) ),
    space_( SpaceRgb )
{}


////////////////////////////////////////////////////////////////////////////////
Color::Color( const uint8_t index ) :
    srgb_( srgb::fromIndex( index ) ),
    space_( SpaceRgb )
{}


////////////////////////////////////////////////////////////////////////////////
Color::Color( const std::string& hexOrName )
{
    const auto rgb32 = rgb32::fromHex( hexOrName );

    if ( rgb32 ) {
        srgb_ = rgb::fromRgb32( rgb32 );
        space_ = SpaceRgb;
        return;
    }

    if ( const auto maybeValue = index::fromName( hexOrName ) ) {
        srgb_ = srgb::fromIndex( maybeValue.value_or( 0 ) );
        space_ = SpaceRgb;
        return;
    }

    //  if parsing of hex and name fails, space stays undefined
}


////////////////////////////////////////////////////////////////////////////////
std::string Color::spaceInfo() const
{
    switch ( space_ ) {
        case SpaceRgb: return "rgb";
        case SpaceHsl: return "hsl";
        case SpaceHsv: return "hsv";
        case SpaceLch: return "lch";
        default: return {};
    }
}


////////////////////////////////////////////////////////////////////////////////
Color Color::rgb() const
{
    switch ( space_ )
    {
        case SpaceRgb: return Color( srgb_, SpaceRgb );
        case SpaceHsl: return Color( rgb::fromHsl( hsl_ ), SpaceRgb );
        case SpaceHsv: return Color( rgb::fromHsv( hsv_ ), SpaceRgb );
        case SpaceLch: return Color( srgb::fromLch( lch_ ), SpaceRgb );
        default: return {};
    }
}


////////////////////////////////////////////////////////////////////////////////
Color Color::hsl() const
{
    switch ( space_ )
    {
        case SpaceRgb: return Color( hsl::fromRgb( srgb_ ), SpaceHsl );
        case SpaceHsl: return Color( hsl_, SpaceHsl );
        case SpaceHsv: return Color( hsl::fromHsv( hsv_ ), SpaceHsl );
        case SpaceLch: return Color( hsl::fromRgb( srgb::fromLch( lch_ ) ), SpaceHsl );
        default: return {};
    }
}


////////////////////////////////////////////////////////////////////////////////
Color Color::hsv() const
{
    switch ( space_ )
    {
        case SpaceRgb: return Color( hsv::fromRgb( srgb_ ), SpaceHsv );
        case SpaceHsl: return Color( hsv::fromHsl( hsl_ ), SpaceHsv );
        case SpaceHsv: return Color( hsv_, SpaceHsv );
        case SpaceLch: return Color( hsv::fromRgb( srgb::fromLch( lch_ ) ), SpaceHsv );
        default: return {};
    }
}


////////////////////////////////////////////////////////////////////////////////
Color Color::lch() const
{
    switch ( space_ )
    {
        case SpaceRgb: return Color( lch::fromSrgb( srgb_ ), SpaceLch );
        case SpaceHsl: return Color( lch::fromSrgb( static_cast<srgb_t>( rgb::fromHsl( hsl_ ) )), SpaceLch );
        case SpaceHsv: return Color( lch::fromSrgb( static_cast<srgb_t>( rgb::fromHsv( hsv_ ) )), SpaceLch );
        case SpaceLch: return Color( lch_, SpaceLch );
        default: return {};
    }
}


////////////////////////////////////////////////////////////////////////////////
col8_t Color::rgb8() const
{
    switch ( space_ )
    {
        case SpaceRgb: return rgb8::fromRgb( srgb_ );
        case SpaceHsl: return rgb8::fromRgb( rgb::fromHsl( hsl_ ) );
        case SpaceHsv: return rgb8::fromRgb( rgb::fromHsv( hsv_ ) );
        case SpaceLch: return rgb8::fromRgb( srgb::fromLch( lch_ ) );
        default: return {};
    }
}


////////////////////////////////////////////////////////////////////////////////
uint32_t Color::rgb32() const
{
    switch ( space_ )
    {
        case SpaceRgb: return rgb32::fromRgb( srgb_ );
        case SpaceHsl: return rgb32::fromRgb( rgb::fromHsl( hsl_ ) );
        case SpaceHsv: return rgb32::fromRgb( rgb::fromHsv( hsv_ ) );
        case SpaceLch: return rgb32::fromRgb( srgb::fromLch( lch_ ) );
        default: return {};
    }
}


////////////////////////////////////////////////////////////////////////////////
uint8_t Color::index() const
{
    switch ( space_ )
    {
        case SpaceRgb: return index::fromRgb( srgb_ );
        case SpaceHsl: return index::fromHsl( hsl_ );
        case SpaceHsv: return index::fromRgb( rgb::fromHsv( hsv_ ) );
        case SpaceLch: return index::fromRgb( srgb::fromLch( lch_ ) );
        default: return {};
    }
}


////////////////////////////////////////////////////////////////////////////////
std::string Color::hex() const
{
    switch ( space_ )
    {
        case SpaceRgb: return hex::fromRgb( srgb_ );
        case SpaceHsl: return hex::fromRgb( rgb::fromHsl( hsl_ ) );
        case SpaceHsv: return hex::fromRgb( rgb::fromHsv( hsv_ ) );
        case SpaceLch: return hex::fromRgb( srgb::fromLch( lch_ ) );
        default: return {};
    }
}


////////////////////////////////////////////////////////////////////////////////
const std::string& Color::name() const
{
    switch ( space_ )
    {
        case SpaceRgb: return name::fromRgb( srgb_ );
        case SpaceHsl: return name::fromRgb( rgb::fromHsl( hsl_ ) );
        case SpaceHsv: return name::fromRgb( rgb::fromHsv( hsv_ ) );
        case SpaceLch: return name::fromRgb( srgb::fromLch( lch_ ) );
        default: {
            //  space should always have a valid value
            assert( true );
            return data::xterm.at( 0 ).name;
        }
    }
}


}   //  ::vivid
