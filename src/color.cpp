#include "vivid/color.h"
#include "vivid/conversion.h"
#include "vivid/encoding.h"
#include "vivid/interpolation.h"
#include "vivid/stream.h"
#include "vivid/utility.h"
#include "vivid/data/xterm.h"

#include <sstream>

namespace vivid {


////////////////////////////////////////////////////////////////////////////////
Color::Color( const rgb_t& rgb ) :
    Color( rgb, Space::Rgb )
{}


////////////////////////////////////////////////////////////////////////////////
Color::Color( const hsl_t& hsl ) :
    Color( hsl, Space::Hsl )
{}


////////////////////////////////////////////////////////////////////////////////
Color::Color( const hsv_t& hsv ) :
    Color( hsv, Space::Hsv )
{}


////////////////////////////////////////////////////////////////////////////////
Color::Color( const lch_t& lch ) :
    Color( lch, Space::Lch )
{}


////////////////////////////////////////////////////////////////////////////////
Color::Color( const col_t& value, const Space space ) :
    value_( value ),
    space_( space )
{}


////////////////////////////////////////////////////////////////////////////////
Color::Color( const col8_t& rgb8 ) :
    srgb_( rgb::fromRgb8( rgb8 ) ),
    space_( Space::Rgb )
{}


////////////////////////////////////////////////////////////////////////////////
Color::Color( const uint32_t rgb32 ) :
    srgb_( rgb::fromRgb32( rgb32 ) ),
    space_( Space::Rgb )
{}


////////////////////////////////////////////////////////////////////////////////
Color::Color( const uint8_t index ) :
    srgb_( srgb::fromIndex( index ) ),
    space_( Space::Rgb )
{}


////////////////////////////////////////////////////////////////////////////////
Color::Color( const std::string& hexOrName )
{
    const auto rgb32 = rgb32::fromHex( hexOrName );

    if ( rgb32 ) {
        srgb_ = rgb::fromRgb32( rgb32 );
        space_ = Space::Rgb;
        return;
    }

    if ( const auto maybeValue = index::fromName( hexOrName ) ) {
        srgb_ = srgb::fromIndex( maybeValue.value_or( 0 ) );
        space_ = Space::Rgb;
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
        case Space::Rgb: return Color( rgb::saturate( srgb_ ), Space::Rgb );
        case Space::Hsl: return Color( rgb::saturate( srgb_ ), Space::Hsl );
        case Space::Hsv: return Color( rgb::saturate( srgb_ ), Space::Hsv );
        case Space::Lch: return Color( lch::saturate( lch_ ), Space::Lch );
        default: assert( true ); return {};
    }
}


////////////////////////////////////////////////////////////////////////////////
bool Color::valid() const
{
    if ( space_ == Space::Undefined ) {
        return false;
    }

    //  concerned space values are non-negative
    if ( glm::any( glm::lessThan( value_, {} ) )) {
        return false;
    }

    if ( space_ == Space::Lch ) {
        return glm::all( glm::lessThan( lch_, { 100, 140, 360 } ));
    }

    return glm::all( glm::lessThanEqual( value_, { 1, 1, 1 } ));
}


////////////////////////////////////////////////////////////////////////////////
std::string Color::spaceInfo() const
{
    switch ( space_ )
    {
        case Space::Rgb: return "rgb";
        case Space::Hsl: return "hsl";
        case Space::Hsv: return "hsv";
        case Space::Lch: return "lch";
        default: assert( true ); return {};
    }
}


////////////////////////////////////////////////////////////////////////////////
std::string Color::quickInfo() const
{
    const auto fg = ansi::fg( index() );
    const auto split = ansi::symbol + " // " + ansi::reset;

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
    const auto spacer = ansi::subtleSymbol + "\u2022 " + ansi::text;
    const auto split = ansi::symbol + " // " + ansi::text;

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
    sstr << ansi::symbol << "space: " << ansi::text << spaceInfo() << ", ";
    sstr << ( valid() ? ( ansi::fg( "green"s ) + "valid" ) : ( ansi::fg( "red"s ) + "invalid" ) ) << "\n";

    sstr << ansi::symbol << "readable: \n";
    sstr << spacer << ansi::colorize( rgb8, "rgb" ) << "\n";
    sstr << spacer << ansi::colorize( hsv::readable( hsv ), "hsv" ) << "\n";
    sstr << spacer << ansi::colorize( hsl::readable( hsl ), "hsl" ) << "\n";
    sstr << spacer << ansi::colorize( xyz::readable( xyz ), "xyz" ) << "\n";

    sstr << ansi::symbol << "unscaled: \n";
    sstr << spacer << ansi::colorize( srgb, "rgb" ) << "\n";
    sstr << spacer << ansi::colorize( hsv, "hsv" ) << "\n";
    sstr << spacer << ansi::colorize( hsl, "hsl" ) << "\n";
    sstr << spacer << ansi::colorize( xyz, "xyz" ) << "\n";
    sstr << spacer << ansi::colorize( lab, "lab" ) << "\n";
    sstr << spacer << ansi::colorize( lch, "lch" );
    sstr << ansi::reset;

    return sstr.str();
}


////////////////////////////////////////////////////////////////////////////////
Color Color::rgb() const
{
    switch ( space_ )
    {
        case Space::Rgb: return Color( srgb_, Space::Rgb );
        case Space::Hsl: return Color( rgb::fromHsl( hsl_ ), Space::Rgb );
        case Space::Hsv: return Color( rgb::fromHsv( hsv_ ), Space::Rgb );
        case Space::Lch: return Color( srgb::fromLch( lch_ ), Space::Rgb );
        default: assert( true ); return {};
    }
}


////////////////////////////////////////////////////////////////////////////////
Color Color::hsl() const
{
    switch ( space_ )
    {
        case Space::Rgb: return Color( hsl::fromRgb( srgb_ ), Space::Hsl );
        case Space::Hsl: return Color( hsl_, Space::Hsl );
        case Space::Hsv: return Color( hsl::fromHsv( hsv_ ), Space::Hsl );
        case Space::Lch: return Color( hsl::fromRgb( srgb::fromLch( lch_ ) ), Space::Hsl );
        default: assert( true ); return {};
    }
}


////////////////////////////////////////////////////////////////////////////////
Color Color::hsv() const
{
    switch ( space_ )
    {
        case Space::Rgb: return Color( hsv::fromRgb( srgb_ ), Space::Hsv );
        case Space::Hsl: return Color( hsv::fromHsl( hsl_ ), Space::Hsv );
        case Space::Hsv: return Color( hsv_, Space::Hsv );
        case Space::Lch: return Color( hsv::fromRgb( srgb::fromLch( lch_ ) ), Space::Hsv );
        default: assert( true ); return {};
    }
}


////////////////////////////////////////////////////////////////////////////////
Color Color::lch() const
{
    switch ( space_ )
    {
        case Space::Rgb: return Color( lch::fromSrgb( srgb_ ), Space::Lch );
        case Space::Hsl: return Color( lch::fromSrgb( static_cast<srgb_t>( rgb::fromHsl( hsl_ ) )), Space::Lch );
        case Space::Hsv: return Color( lch::fromSrgb( static_cast<srgb_t>( rgb::fromHsv( hsv_ ) )), Space::Lch );
        case Space::Lch: return Color( lch_, Space::Lch );
        default: assert( true ); return {};
    }
}


////////////////////////////////////////////////////////////////////////////////
col8_t Color::rgb8() const
{
    switch ( space_ )
    {
        case Space::Rgb: return rgb8::fromRgb( srgb_ );
        case Space::Hsl: return rgb8::fromRgb( rgb::fromHsl( hsl_ ) );
        case Space::Hsv: return rgb8::fromRgb( rgb::fromHsv( hsv_ ) );
        case Space::Lch: return rgb8::fromRgb( srgb::fromLch( lch_ ) );
        default: assert( true ); return {};
    }
}


////////////////////////////////////////////////////////////////////////////////
uint32_t Color::rgb32() const
{
    switch ( space_ )
    {
        case Space::Rgb: return rgb32::fromRgb( srgb_ );
        case Space::Hsl: return rgb32::fromRgb( rgb::fromHsl( hsl_ ) );
        case Space::Hsv: return rgb32::fromRgb( rgb::fromHsv( hsv_ ) );
        case Space::Lch: return rgb32::fromRgb( srgb::fromLch( lch_ ) );
        default: assert( true ); return {};
    }
}


////////////////////////////////////////////////////////////////////////////////
uint8_t Color::index() const
{
    switch ( space_ )
    {
        case Space::Rgb: return index::fromRgb( srgb_ );
        case Space::Hsl: return index::fromHsl( hsl_ );
        case Space::Hsv: return index::fromRgb( rgb::fromHsv( hsv_ ) );
        case Space::Lch: return index::fromRgb( srgb::fromLch( lch_ ) );
        default: assert( true ); return {};
    }
}


////////////////////////////////////////////////////////////////////////////////
std::string Color::hex() const
{
    switch ( space_ )
    {
        case Space::Rgb: return hex::fromRgb( srgb_ );
        case Space::Hsl: return hex::fromRgb( rgb::fromHsl( hsl_ ) );
        case Space::Hsv: return hex::fromRgb( rgb::fromHsv( hsv_ ) );
        case Space::Lch: return hex::fromRgb( srgb::fromLch( lch_ ) );
        default: assert( true ); return {};
    }
}


////////////////////////////////////////////////////////////////////////////////
const std::string& Color::name() const
{
    switch ( space_ )
    {
        case Space::Rgb: return name::fromRgb( srgb_ );
        case Space::Hsl: return name::fromRgb( rgb::fromHsl( hsl_ ) );
        case Space::Hsv: return name::fromRgb( rgb::fromHsv( hsv_ ) );
        case Space::Lch: return name::fromRgb( srgb::fromLch( lch_ ) );
        default: assert( true ); return data::xterm.at( 0 ).name;
    }
}


}   //  ::vivid
