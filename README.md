# vivid 🌈
A simple-to-use `cpp` color library

- **strongly-typed** colors
- color space **conversions**
- perceptual color **interpolation**
- popular and custom **color maps**
- **xterm** names and **ansi** codes
- ansi **escape sequences** and **html** encoding
- (somewhat) **unit tested** in itself and against `QColor`
- **qmake** and **cmake** support

```cpp
using namespace vivid;

//  create and interpolate colors
Color c1( "indianred" );
Color c2 = hsl_t( 0.f, 0.4f, 0.5f );

auto interp = lerpLch( c1, c2, 0.5f );   //  perceptual interpolation in L*C*h(ab)
std::string hex = interp.hex();

//  quick access to popular colormaps for data visualization
ColorMap cmap( ColorMap::PresetViridis );
Color mid = cmap.at( 0.5f );

//  ansi and html encodings
std::cout << ansi::fg( 163 ) << "woah!!" << ansi::reset;
fout << html::bg( "#abc123" ) << "styled background color" << html::close;
```

##  Content

<!-- TOC depthFrom:2 depthTo:2 withLinks:1 updateOnSave:1 orderedList:0 -->

- [Content](#content)
- [Motivation](#motivation)
- [Getting Started](#getting-started)
- [Dependencies](#dependencies)
- [Types](#types)
- [Color Spaces](#color-spaces)
- [Interpolation](#interpolation)
- [Color Maps](#color-maps)
- [Encodings](#encodings)
- [Attributions](#attributions)

<!-- /TOC -->


## Motivation

Things we create should be beautiful. Be it a console log message or a real-time volumetric data plot. I'm working with colors quite often, but found the available means to work with them lacking. Especially if you want to just get stuff (he said stuff) done and your ideas down in code. Over time, I gathered all the little snippets and helpers I had created, and thus this project was born.

`vivid` allows you to quickly create, lookup and convert colors. It provides perceptual color interpolation, easy access to color names, ascii escape codes and to some of the great data visualization color palettes out there.


## Getting Started

```bash
git clone git@github.com:gurki/vivid.git
git submodule update --init
```

This repository comes with support for both `qmake` (_vivid.pri_) and `cmake` projects.
You can try it out by simply opening up `examples/qmake/vivid.pro` in `Qt Creator`, or running

```bash
mkdir build && cd build
cmake .. && make
./examples/cmake/vivid_example
```


## Dependencies

`vivid`  depends on a small number of header-only libraries, which are mostly included as submodules.

- Nlohmann's great [Json for Modern C++](https://github.com/nlohmann/json) to load color names and color maps
- [OpenGL Mathematics (GLM)](https://github.com/g-truc/glm) for vector type and operations
- [Catch2](https://github.com/catchorg/Catch2/tree/master/examples) for testing


## High-Level API ⛰️

`vivid` provides a convenient `Color` class, which is intended to be flexible and easy to use. It stores the `value` (_col_t_) and the associated `space` _∈ {`RGB`, `HSV`, `HSL`, `LCH`}_ of its underlying type. `Colors` can be implicitly constructed from any of the above native color spaces and their representations (c.f. _include/vivid/color.h_ for all available constructors).

```cpp
//  instantiation
Color col1( "#abcdef" );
Color col2 = { 255, 0, 128 };
Color col3 = { 1.f, 0.3f, 0.6f }, Color::SpaceHsl );
```

Conversions to other color spaces are directly available using e.g. `col.hsl()` or `col.hex()`. Moving to one of the four native spaces will return another `Color` instance with its `value` and `space` converted accordingly.

```cpp
//  native conversion
Color conv = col1.hsl();    //  convert to hsl, whatever the current space
col1.spaceInfo();   //  rgb
conv.spaceInfo();   //  hsl
```

`8-bit` colors are represented using either byte-triplets (_col8_t_) or compactly as `ARGB` (_uint32_t_), where alpha is set to `0xff` by default. Lossy conversion, e.g. getting the name or index of some non-xterm color, will return the closest valid color/value in that space.

```cpp
//  lossy conversion
Color original( "#a1b2c3" );
Color lossy = original.index(); //  clamps to nearest ansi color code
original.hex(); //  #a1b2c3
lossy.hex();    //  #afafd7
```

## Low-Level API 🛠️

Under the hood, `vivid` uses inheritance-based **strong typing**, where the base _col_t_-type aliases directly to _glm::vec<3, float>_ (c.f. _include/vivid/types.h_). Parenting to a `glm` vector type allows efficient and effective handling of colors using all of `glm`'s vector goodness right out of the box.

## Color Spaces

Under the hood, `vivid` uses an extensive set of inheritance-based **strongly-typed** conversions between color spaces (c.f. _include/vivid/conversion.h_). All of these methods are built in a functional way, where colors get passed through converters, yielding new colors in different spaces.

### Direct Conversions

The following direct conversions are currently available.

    adobe ← xyz
    hex ← rgb8, index
    hsl ← rgb, index
    hsv ← rgb
    index ← rgb8, name
    lab ← xyz, lch
    lch ← lab
    linear ← srgb
    name ← index
    rgb ← rgb8, hsv, hsl
    rgb32 ← rgb, hex
    rgb8 ← rgb, rgb32, index
    srgb ← xyz
    xyz ← lab, srgb, adobe

### RGB Working Spaces

The `Color` class assumes a default `sRGB` working space. Specifically, the conversion between `RGB` and `XYZ` applies `sRGB` compounding and inverse compounding. You can however extend this freely and work with custom color spaces using the low-level API. If you have no idea what I just said, don't worry - I didn't either a couple weeks ago :).

    You can use this library as high- or low-level as you like!

```cpp
//  manual wide-gamut rgb to xyz conversion

rgb_t wg = { 1.f, 0.f, 0.f };

//  working space matrix from primary color chromaticities and white point
const glm::vec2 d50 = { 0.3457f, 0.3585f };
const glm::vec3 ciex = { 0.7347f, 0.1152f, 0.1566f };
const glm::vec3 ciey = { 0.2653f, 0.8264f, 0.0177f };
const auto wg_to_xyz = workingSpaceMatrix( d50, ciex, ciey );

//  linearized rgb via inverse gamma compounding
const float gamma = 2.19921875f;
auto linear = rgb::gamma( wg, gamma );

//  xyz with d50 white point using the computed linear transformation
auto xyz50 = wg_to_xyz * linear;
```

Note that `vivid` assumes a default `D65` white point, which means chromatic adaptation should be applied after above result in order to work properly with e.g. `srgb::fromXyz()` conversions.


## Interpolation

```cpp
//  pseudo-code to generate the images in this section
for ( auto& pixel : image ) {
    const float t = pixel.x / image.width;
    const Color col = lerpLch( c1, c2, t );
    image.setColor( pixel, col );
}
```

Color interpolation is an interesting topic. What should the color halfway in-between <span style="color:rgb(178, 76, 76)">red</span> and <span style="color:rgb(25, 153, 102)">green</span> look like? There is a great article introducing this topic by Grego Aisch [^1]. In order to do a perceptually linear transition from one color to another, we can't simply linearly interpolate two _RGB_-vectors. Rather, we move to a more suitable color space, interpolate there, and then move back again. Namely, we use the _CIE L\*C\*h(ab)_ space, or _LCH_, which matches the human visual system rather well. There are more suitable color spaces nowadays to do so, but _LCH_ has a nice balance between complexity (code and computation) and outcome.

Compare the following table to get an idea of interpolating in different color spaces.

Color Space   | Linear Interpolation
--------------|-------------------------------------------------------------------
RGB           | ![lerp-rgb](docs/images/interpolations/lerpRgb.png)
LCH           | ![lerp-lch](docs/images/interpolations/lerpLch.png)
HSV           | ![lerp-hsv](docs/images/interpolations/lerpHsv.png)
HSL (Clamped) | ![lerp-hsl-clamped](docs/images/interpolations/lerpHslClamped.png)

`vivid` provides low-level interpolations for the four main spaces `RGB, HSL, HSV, LCH`. They can be accessed directly via e.g. `rgb::lerp( const col_t&, const col_t&, const float )`, or implicitly via `lerp( const Color&, const Color&, const float )`. Note, that the latter requires the `Color` objects to be in the same space. Otherwise, an invalid color is returned.

[\^1] [Grego Aisch (2011) - How To Avoid Equidistant HSV Colors](https://www.vis4.net/blog/2011/12/avoid-equidistant-hsv-colors/)


## Color Maps

`vivid` comes with a set of pre-defined color maps, which I conveniently gathered under one umbrella. Thanks to the awesome community out there for their great work! [\^2,\^3]

As shown in the example in the beginning, it's quick and easy to query colors from a certain color map. You can also create your own maps by simply loading an according _\*.json_ file.

```cpp
//  loading a custom color map
ColorMap cmap( "res/colormaps/mycolormap.json" );
auto mid = cmap.at( 0.5f );
```

Name        | Image
------------|----------------------------------------------------
Inferno     | ![inferno](docs/images/colormaps/inferno.png)
Magma       | ![magma](docs/images/colormaps/magma.png)
Plasma      | ![plasma](docs/images/colormaps/plasma.png)
Viridis     | ![viridis](docs/images/colormaps/viridis.png)
Vivid       | ![vivid](docs/images/colormaps/vivid.png)
Rainbow     | ![vivid](docs/images/colormaps/rainbow.png)
Hsl         | ![hsl](docs/images/colormaps/hsl.png)
Hsl Pastel  | ![hsl-pastel](docs/images/colormaps/hsl-pastel.png)
Blue-Yellow | ![vivid](docs/images/colormaps/blue-yellow.png)
Cool-Warm   | ![vivid](docs/images/colormaps/cool-warm.png)  |  

[\^2] [Stefan & Nathaniel - MPL Colormaps](http://bids.github.io/colormap/) <br>
[\^3] [SciVisColor](https://sciviscolor.org/)


## Encodings

`vivid` provides encodings for **ansi** escape codes (pretty console <3) and **html** using spans.

### ANSI

You can colorize console messages very simply using the `vivid::ansi` helpers.

```cpp
std::cout << ansi::fg( 136 ) << "and tada, colorized font" << ansi::reset;
```

To get an overview of all color codes or quickly check if your console has 8-bit color support, you can call `printColorTable()` (shoutout to Gawin [^4] for the layout idea).

![colortable](docs/images/console/color-table.png)

Escape codes can also be used in conjunction with `ColorMaps` to create some joyful effects.

```cpp
ColorMap rainbowMap( ColorMap::PresetRainbow );
std::string text = "How can you tell? - Raaaaaaiiiinbooooooowwws.";
std::cout << ansi::colorize( text, rainbowMap ) << std::endl;
```

![rainbows](docs/images/console/rainbow-text.png)


### HTML

One of my side projects is a tagged logging system, where one of the sinks goes to html. This has become very handy.

```cpp
Color col( "LightSteelBlue" );
fout << html::fg( col ) << "colorized html text!" << html::close;
//  <span style='color:rgb(175, 175, 255)'>colorized html text!</span>
```

[^4] [Gawin's xterm color demo](https://github.com/gawin/bash-colors-256)


## Attributions

Massive thanks to all the colour enthusiasts out there for references and material, without which this project would not have been possible.
Shoutout and thanks to the community over at [r/cpp](https://www.reddit.com/r/cpp/comments/bpu0hl/vivid_a_simpletouse_cpp_color_library) for comments, feedback and suggestions! <3
