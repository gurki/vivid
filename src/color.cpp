#include "vivid/color.h"
#include "vivid/colortable.h"
#include "vivid/conversion.h"
#include "vivid/functions.h"
#include "vivid/stream.h"

namespace tq {


//////////////////////////////////////////////////////////////////////////////////
//Color::Color( const col_t& col, const Space space ) :
//    value_( col ),
//    space_( space )
//{}


//////////////////////////////////////////////////////////////////////////////////
//std::string Color::spaceInfo() const
//{
//    switch ( space_ ) {
//        case SpaceRgb: return "rgb";
//        case SpaceHsl: return "hsl";
//        case SpaceHsv: return "hsv";
//        case SpaceHcl: return "hcl";
//        default: return {};
//    }
//}


//////////////////////////////////////////////////////////////////////////////////
//Color Color::rgb() const
//{
//    switch ( space_ )
//    {
//        case SpaceRgb: return Color( value_, SpaceRgb );
//        case SpaceHsl: return Color( tq::rgb::fromHsl( value_ ), SpaceRgb );
//        case SpaceHsv: return Color( tq::rgb::fromHsv( value_ ), SpaceRgb );
//        case SpaceHcl: return Color( tq::rgb::fromHcl( value_ ), SpaceRgb );
//        default: return {};
//    }
//}


//////////////////////////////////////////////////////////////////////////////////
//Color Color::hsl() const
//{
//    switch ( space_ )
//    {
//        case SpaceRgb: return Color( tq::hsl::fromRgb( value_ ), SpaceHsl );
//        case SpaceHsl: return Color( value_, SpaceHsl );
//        case SpaceHsv: return Color( tq::hsl::fromHsv( value_ ), SpaceHsl );
//        case SpaceHcl: return Color( tq::hsl::fromRgb( tq::rgb::fromHcl( value_ ) ), SpaceHsl );
//        default: return {};
//    }
//}


//////////////////////////////////////////////////////////////////////////////////
//Color Color::hsv() const
//{
//    switch ( space_ )
//    {
//        case SpaceRgb: return Color( tq::hsv::fromRgb( value_ ), SpaceHsv );
//        case SpaceHsl: return Color( tq::hsv::fromHsl( value_ ), SpaceHsv );
//        case SpaceHsv: return Color( value_, SpaceHsv );
//        case SpaceHcl: return Color( tq::hsv::fromRgb( tq::rgb::fromHcl( value_ ) ), SpaceHsv );
//        default: return {};
//    }
//}


//////////////////////////////////////////////////////////////////////////////////
//Color Color::hcl() const
//{
//    switch ( space_ )
//    {
//        case SpaceRgb: return Color( tq::hcl::fromRgb( value_ ), SpaceHcl );
//        case SpaceHsl: return Color( tq::hcl::fromRgb( tq::rgb::fromHsl( value_ ) ), SpaceHcl );
//        case SpaceHsv: return Color( tq::hcl::fromRgb( tq::rgb::fromHsv( value_ ) ), SpaceHcl );
//        case SpaceHcl: return Color( value_, SpaceHcl );
//        default: return {};
//    }
//}


//////////////////////////////////////////////////////////////////////////////////
//col8_t Color::rgb8() const
//{
//    switch ( space_ )
//    {
//        case SpaceRgb: return tq::rgb8::fromRgb( value_ );
//        case SpaceHsl: return tq::rgb8::fromRgb( tq::rgb::fromHsl( value_ ) );
//        case SpaceHsv: return tq::rgb8::fromRgb( tq::rgb::fromHsv( value_ ) );
//        case SpaceHcl: return tq::rgb8::fromRgb( tq::rgb::fromHcl( value_ ) );
//        default: return {};
//    }
//}


//////////////////////////////////////////////////////////////////////////////////
//uint32_t Color::rgb32() const
//{
//    switch ( space_ )
//    {
//        case SpaceRgb: return tq::rgb32::fromRgb( value_ );
//        case SpaceHsl: return tq::rgb32::fromRgb( tq::rgb::fromHsl( value_ ) );
//        case SpaceHsv: return tq::rgb32::fromRgb( tq::rgb::fromHsv( value_ ) );
//        case SpaceHcl: return tq::rgb32::fromRgb( tq::rgb::fromHcl( value_ ) );
//        default: return {};
//    }
//}


//////////////////////////////////////////////////////////////////////////////////
//uint8_t Color::index() const
//{
//    switch ( space_ )
//    {
//        case SpaceRgb: return tq::index::fromRgb( value_ );
//        case SpaceHsl: return tq::index::fromHsl( value_ );
//        case SpaceHsv: return tq::index::fromRgb( tq::rgb::fromHsv( value_ ) );
//        case SpaceHcl: return tq::index::fromRgb( tq::rgb::fromHcl( value_ ) );
//        default: return {};
//    }
//}


//////////////////////////////////////////////////////////////////////////////////
//std::string Color::hex() const
//{
//    switch ( space_ )
//    {
//        case SpaceRgb: return tq::hex::fromRgb( value_ );
//        case SpaceHsl: return tq::hex::fromRgb( tq::rgb::fromHsl( value_ ) );
//        case SpaceHsv: return tq::hex::fromRgb( tq::rgb::fromHsv( value_ ) );
//        case SpaceHcl: return tq::hex::fromRgb( tq::rgb::fromHcl( value_ ) );
//        default: return {};
//    }
//}


//////////////////////////////////////////////////////////////////////////////////
//std::string Color::name() const
//{
//    switch ( space_ )
//    {
//        case SpaceRgb: return tq::name::fromRgb( value_ );
//        case SpaceHsl: return tq::name::fromRgb( tq::rgb::fromHsl( value_ ) );
//        case SpaceHsv: return tq::name::fromRgb( tq::rgb::fromHsv( value_ ) );
//        case SpaceHcl: return tq::name::fromRgb( tq::rgb::fromHcl( value_ ) );
//        default: return {};
//    }
//}


//////////////////////////////////////////////////////////////////////////////////
//Color Color::fromRgb( const col_t& rgb ) {
//    return Color( rgb, SpaceRgb );
//}


//////////////////////////////////////////////////////////////////////////////////
//Color Color::fromHsl( const col_t& hsl ) {
//    return Color( hsl, SpaceHsl );
//}


//////////////////////////////////////////////////////////////////////////////////
//Color Color::fromHsv( const col_t& hsv ) {
//    return Color( hsv, SpaceHsv );
//}


//////////////////////////////////////////////////////////////////////////////////
//Color Color::fromHcl( const col_t& hcl ) {
//    return Color( hcl, SpaceHcl );
//}


//////////////////////////////////////////////////////////////////////////////////
//Color Color::fromRgb8( const col8_t& rgb8 ) {
//    return Color( tq::rgb::fromRgb8( rgb8 ), SpaceRgb );
//}


//////////////////////////////////////////////////////////////////////////////////
//Color Color::fromRgb32( const uint32_t rgb32 ) {
//    return Color( tq::rgb::fromRgb32( rgb32 ), SpaceRgb );
//}


//////////////////////////////////////////////////////////////////////////////////
//Color Color::fromIndex( const uint8_t index )
//{
//    if ( ColorTable::empty() ) {
//        return {};
//    }

//    return Color( tq::rgb::fromIndex( index ), SpaceRgb );
//}


//////////////////////////////////////////////////////////////////////////////////
//Color Color::fromHex( const std::string& hex ) {
//    return Color( tq::rgb::fromHex( hex ), SpaceRgb );
//}


//////////////////////////////////////////////////////////////////////////////////
//Color Color::fromName( const std::string& name ) {
//    return Color( tq::rgb::fromName( name ), SpaceRgb );
//}


//////////////////////////////////////////////////////////////////////////////////
//Color lerp( const Color& c1, const Color& c2, const float t )
//{
//    if ( c1.space() != c2.space() ) {
//        return {};
//    }

//    switch ( c1.space() ) {
//        case Color::SpaceRgb: return Color::fromRgb( tq::rgb::lerp( c1.value(), c2.value(), t ) );
//        case Color::SpaceHsl: return Color::fromHsl( tq::hsl::lerp( c1.value(), c2.value(), t ) );
//        case Color::SpaceHsv: return Color::fromHsv( tq::hsv::lerp( c1.value(), c2.value(), t ) );
//        case Color::SpaceHcl: return Color::fromHcl( tq::hcl::lerp( c1.value(), c2.value(), t ) );
//        default: return {};
//    }
//}


//////////////////////////////////////////////////////////////////////////////////
//std::ostream& operator << ( std::ostream& out, const Color& col )
//{
//    out << col.spaceInfo() << "(";
//    out << std::setprecision( 3 ) << col.value().x << ", " << col.value().y << ", " << col.value().z;
//    out << ")";

//    return out;
//}


}   //  ::tq
