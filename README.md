# vivid 🌈
A simple-to-use `cpp` color library

- color space **conversions**
- perceptual color **interpolation**
- popular and custom **color maps**
- **xterm** names and **ansi** codes
- ansi **escape sequences** and **html** encoding
- (somewhat) **unit tested** in itself and against `QColor`

```cpp
using namespace vivid;

//  create and interpolate colors
Color c1( "indianred" );
Color c2( { 0.f, 0.4f, 0.5f }, Color::SpaceHsl );

auto interp = lerp( c1, c2, 0.5f );
std::string hex = interp.hex();

//  quick access to popular colormaps for data visualization
ColorMap cmap( ColorMap::Viridis );
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

This repository comes with support for ~~both~~ `Qt` (_vivid.pri_) ~~and `cmake` (_CMakeList_)~~ projects.
You can start by simply opening up `examples/qmake/vivid.pro` in `Qt Creator`.


## Dependencies

`vivid`  depends on a small number of header-only libraries, which are mostly included as submodules.

- Nlohmann's great [Json for Modern C++](https://github.com/nlohmann/json) to load color names and color maps
- [OpenGL Mathematics (GLM)](https://github.com/g-truc/glm) for vector type and operations
- [Catch2](https://github.com/catchorg/Catch2/tree/master/examples) for testing


## Types

`vivid` provides a convenient `Color` class, which is intended to be flexible and easy to use. It stores colors as combination of float-triplet `values` (`col_t ≡ glm::vec<3, float>`) and their associated `space ∈ {RGB, HSV, HSL, LCH}`. It can be implicitly constructed from any of the supported color formats and spaces, e.g. `Color col( "#abcdef" );`. Conversions to other color spaces are directly available using e.g. `col.hsl()` or `col.hex()`. 8-bit colors are represented using either byte-triplets (`col8_t ≡ glm::vec<3, uint8_t>`) or compactly as `uint32_t` (`ARGB`), where alpha is set to `0xff` by default. Lossy conversion, e.g. getting the name or index of some non-xterm color, will return the closest valid color/value in that space.


## Color Spaces

Under the hood, `vivid` uses an extensive set of direct conversions (c.f. `include/vivid/conversion.h`). It additionally provides a bunch of shortcuts for multi-step conversions. All of these methods are built in a functional way, where colors get passed through converters, yielding new colors in different spaces. The caller must (to some degree) ensure the integrity of the input data passed. E.g. `vivid::xyz::fromLab` indeed assumes, that it is handed a `vivid::col_t` encoding a valid `L*a*b` color representation.

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

`vivid` assumes a default `sRGB` working space. Specifically, the conversion between `RGB` and `XYZ` applies `sRGB` compounding and inverse compounding. You can also extend this using the low-level API.

```cpp
//  manual wide gamut rgb to xyz conversion
static const float wideGamutGamma = 2.2f;
static const glm::mat3 wideToXyz = {    //  will be transposed due to column-major init
    0.7161046f, 0.1009296f, 0.1471858f,
    0.2581874f, 0.7249378f, 0.0168748f,
    0.0000000f, 0.0517813f, 0.7734287f
};

col_t wide = { 1.f, 0.f, 0.f };
auto linear = rgb::invGamma( wide, wideGamutGamma );
auto xyz = linear * wideToXyz;          //  post-multiply to save transposition
```


## Interpolation

```cpp
//  pseudo-code to generate the images in this section
for ( auto& pixel : image ) {
    const float t = pixel.x / image.width;
    const auto col = lerp( c1, c2, t );
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
ColorMap cmap( VIVID_ROOT_PATH "res/colormaps/mycolormap.json" );
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

![colortable](docs/images/console/colortable.png)

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

Shoutout and thanks to the great reddit community over at [r/cpp](https://www.reddit.com/r/cpp/comments/bpu0hl/vivid_a_simpletouse_cpp_color_library) for comments, feedback and suggestions! <3
