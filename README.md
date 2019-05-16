# vivid
A simple-to-use `cpp` color library

```cpp
using namespace tq;

col_t c1 = rgb::fromName( "indianred" );
col_t c2 = rgb::fromHsl( { 0.f, 0.4f, 0.5f } );

col_t rgb = rgb::lerp( c1, c2, 0.5f );
col_t hsv = rgb::lerpHsv( c1, c2, 0.5f );
col_t lch = rgb::lerpHcl( c1, c2, 0.5f );

std::string hex = hex::fromRgb( lch );

//  color map
ColorMap cmap;
cmap.load( VIVID_ROOT_PATH "/res/colormaps/viridian.json" );
cmap.interpolation = ColorMap::Interpolation::Hcl;

col_t c3 = cmap.at( 0.5f );
```


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


## Interpolation

Color Space   | Linear Interpolation
--------------|-------------------------------------------------------------------
RGB           | ![lerp-rgb](docs/images/interpolations/lerpRgb.png)
HCL           | ![lerp-cielch](docs/images/interpolations/lerpHcl.png)
HSV           | ![lerp-hsv](docs/images/interpolations/lerpHsv.png)
HSL (Clamped) | ![lerp-hsl-clamped](docs/images/interpolations/lerpHslClamped.png)


## Color Maps

Name     | Image
---------|----------------------------------------------
Inferno  | ![inferno](docs/images/colormaps/inferno.png)
Magma    | ![magma](docs/images/colormaps/magma.png)
Plasma   | ![plasma](docs/images/colormaps/plasma.png)
Viridian | ![viridis](docs/images/colormaps/viridis.png)
