#include "vivid/color.h"
#include "vivid/conversion.h"
#include "vivid/functions.h"
#include "vivid/interpolation.h"
#include "vivid/stream.h"
#include "vivid/data/xterm.h"
#include "vivid/encoding.h"

#include <sstream>

namespace vivid {


////////////////////////////////////////////////////////////////////////////////
Color::Color( const rgb_t& rgb ) :
    Color( rgb, SpaceRgb )
{}


////////////////////////////////////////////////////////////////////////////////
Color::Color( const hsl_t& hsl ) :
    Color( hsl, SpaceHsl )
{}


////////////////////////////////////////////////////////////////////////////////
Color::Color( const hsv_t& hsv ) :
    Color( hsv, SpaceHsv )
{}


////////////////////////////////////////////////////////////////////////////////
Color::Color( const lch_t& lch ) :
    Color( lch, SpaceLch )
{}


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
Color::Color( const uint8_t r, const uint8_t g, const uint8_t b ) :
    Color( rgb::fromRgb8( { r, g, b } ) )
{}


////////////////////////////////////////////////////////////////////////////////
Color Color::saturated() const
{
    switch ( space_ )
    {
        case SpaceRgb: return Color( rgb::saturate( srgb_ ), SpaceRgb );
        case SpaceHsl: return Color( rgb::saturate( srgb_ ), SpaceHsl );
        case SpaceHsv: return Color( rgb::saturate( srgb_ ), SpaceHsv );
        case SpaceLch: return Color( lch::saturate( lch_ ), SpaceLch );
        default: assert( true ); return {};
    }
}


////////////////////////////////////////////////////////////////////////////////
bool Color::valid() const
{
    if ( space_ == SpaceUndefined ) {
        return false;
    }

    //  concerned space values are non-negative
    if ( glm::any( glm::lessThan( value_, {} ) )) {
        return false;
    }

    if ( space_ == SpaceLch ) {
        return glm::all( glm::lessThan( lch_, { 100, 140, 360 } ));
    }

    return glm::all( glm::lessThanEqual( value_, { 1, 1, 1 } ));
}


////////////////////////////////////////////////////////////////////////////////
std::string Color::spaceInfo() const
{
    switch ( space_ )
    {
        case SpaceRgb: return "rgb";
        case SpaceHsl: return "hsl";
        case SpaceHsv: return "hsv";
        case SpaceLch: return "lch";
        default: assert( true ); return {};
    }
}


////////////////////////////////////////////////////////////////////////////////
std::string Color::quickInfo() const
{
    const auto fg = ansi::fg( index() );
    const auto split = ansi::grey150 + " // " + ansi::reset;

    std::stringstream sstr;
    sstr << fg << hex();
    sstr << split << fg << std::setw( 3 ) << std::right << int( index() );
    sstr << split << fg << std::setw( 17 ) << std::left << name();
    sstr << ansi::reset;

    return sstr.str();
}


////////////////////////////////////////////////////////////////////////////////
std::string Color::info() const
{
    const auto fg = ansi::fg( index() );
    const auto spacer = ansi::grey100 + "\u2022 " + ansi::reset;
    const auto split = ansi::grey150 + " // " + ansi::reset;

    const auto rgb8 = this->rgb8();
    const auto srgb = this->rgb().srgb_;
    const auto hsv = this->hsv().hsv_;
    const auto hsl = this->hsl().hsl_;
    const auto lch = this->lch().lch_;
    const auto xyz = xyz::fromSrgb( srgb );
    const auto lab = lab::fromXyz( xyz );

    using namespace std::string_literals;

    std::stringstream sstr;
    sstr << quickInfo() << "\n";
    sstr << ansi::grey150 << "space: " << ansi::reset << spaceInfo() << ", ";
    sstr << ( valid() ? ( ansi::fg( "green"s ) + "valid" ) : ( ansi::fg( "red"s ) + "invalid" ) ) << "\n";

    sstr << ansi::grey150 << "readable: \n";
    sstr << spacer << ansi::colorize( rgb8, "rgb" ) << "\n";
    sstr << spacer << ansi::colorize( hsv::readable( hsv ), "hsv" ) << "\n";
    sstr << spacer << ansi::colorize( hsl::readable( hsl ), "hsl" ) << "\n";
    sstr << spacer << ansi::colorize( xyz::readable( xyz ), "xyz" ) << "\n";

    sstr << ansi::grey150 << "unscaled: \n";
    sstr << spacer << ansi::colorize( srgb, "rgb" ) << "\n";
    sstr << spacer << ansi::colorize( hsv, "hsv" ) << "\n";
    sstr << spacer << ansi::colorize( hsl, "hsl" ) << "\n";
    sstr << spacer << ansi::colorize( xyz, "xyz" ) << "\n";
    sstr << spacer << ansi::colorize( lab, "lab" ) << "\n";
    sstr << spacer << ansi::colorize( lch, "lch" );

    return sstr.str();
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
        default: assert( true ); return {};
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
        default: assert( true ); return {};
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
        default: assert( true ); return {};
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
        default: assert( true ); return {};
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
        default: assert( true ); return {};
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
        default: assert( true ); return {};
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
        default: assert( true ); return {};
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
        default: assert( true ); return {};
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
        default: assert( true ); return data::xterm.at( 0 ).name;
    }
}


}   //  ::vivid
