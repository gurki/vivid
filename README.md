# vivid
A simple-to-use `cpp` color library

```cpp
tq::col_t c1 = tq::rgb::fromName( "indianred" );
tq::col_t c2 = tq::rgb::fromHsl( { 0.f, 0.4f, 0.5f } );

const auto rgb = tq::rgb::lerp( c1, c2, 0.5 );
const auto hsv = tq::rgb::lerpHsv( c1, c2, 0.5 );
const auto lch = tq::rgb::lerpHcl( c1, c2, 0.5 );

const auto hex = tq::hex::fromRgb( lch );
```

Color Space   | Linear Interpolation
--------------|-------------------------------------------------------------------
RGB           | ![lerp-rgb](docs/images/interpolations/lerpRgb.png)
CIELch        | ![lerp-cielch](docs/images/interpolations/lerpHcl.png)
HSV           | ![lerp-hsv](docs/images/interpolations/lerpHsv.png)
HSL (Clamped) | ![lerp-hsl-clamped](docs/images/interpolations/lerpHslClamped.png)


## Motivation

Things we create should be beautiful. Be it a console log message or a real-time volumetric data plot. I'm working with colors quite often, but found the available means to work with them lacking. Especially if you want to just get some shit done and your ideas down on paper.

Over time, I wrote all the small helpers now contained in this pet project of mine, which help me create, lookup and convert colors. It also lets me quickly interpolate in different color spaces or use some of the great data visualization color palettes out there.


## Color Spaces

`vivid` has an extensive set of direct conversion routines. Additionally, there's a bunch of shortcuts for multi-step conversions. I haven't included the complete graph of all possible conversions. Rather every function present has been of use to me at least once.

### Native Conversions

    hcl ← lab
    hex ← rgb8, index
    hsl ← rgb, index
    hsv ← rgb
    index ← rgb8, name
    lab ← xyz, hcl
    name ← index
    rgb ← rgb8, hsv, hsl, xyz
    rgb32 ← rgb, hex
    rgb8 ← rgb, rgb32, index
    xyz ← lab, rgb
