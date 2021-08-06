# Changelog
All notable changes to this project will be documented in this file.
The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/), and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).


## [v3.0.1] - 2021-08-06

### Added
- Start interpolation and wrapping test cases

### Fixed
- Faulty LCH interpolation wrapping [\#17](https://github.com/gurki/vivid/pull/17)


## [v3.0.0] - 2021-02-22

### Added
- Add interpolation in `Linear RGB` for `Color`
- Add convenience `Color::linearRgb()` getter
- Add gamma correction section and example to README
- Clarify `Color::Space::Rgb` usage and default `sRGB` working space
- Add [Björn Ottoson's Oklab](https://bottosson.github.io/posts/oklab/) perceptual color space [\#13](https://github.com/gurki/vivid/pull/13)

### Changed
- Update json to `v3.9.1` and replace implicit conversions [\#9](https://github.com/gurki/vivid/pull/9)
- Deprecate submodules in favor of FetchContent API (cmake >3.14) [\#10](https://github.com/gurki/vivid/pull/10)
- Migrate qmake examples and tests to cmake [\#11](https://github.com/gurki/vivid/pull/11) [\#12](https://github.com/gurki/vivid/pull/12)

### Fixed
- Faulty HSV conversion from greys [\#14](https://github.com/gurki/vivid/pull/14)


## [v2.2.2] - 2020-11-20

### Fixed
- Missing sign in bradford's constant [\#8](https://github.com/gurki/vivid/issues/8)


## [v2.2.1] - 2019-09-19

### Changed
- Update submodule paths to https


## [v2.2.0] - 2019-09-10

### Added
- Add Google Turbo colormap preset [\#6](https://github.com/gurki/vivid/pull/6)

### Fixed
- Use correct standard library math functions, add missing header includes [\#5](https://github.com/gurki/vivid/pull/5)


## [v2.1.0] - 2019-06-04

### Changed
- Replace enums by enum classes


## [v2.0.0] - 2019-05-25

### Added
- Introduce inheritance-based strong typing
- Add color info strings
- Add hand-picked default colors
- Add color validity check
- Add explicit ANSI grey scale map
- Add white point and working space utilities
- Add working space unit tests

### Changed
- Move `printColorTable` to `vivid::ansi` namespace
- Rework everything to strong types
- Rename functions to utility

### Fixed
- Fix some `LAB` and `XYZ` bugs
- Fix conversion matrix number twist

### Removed
- Remove automatic color saturation in low-level conversions
- Remove additional line breaks around color table print


## [v1.1.2] - 2019-05-20

### Changed
- Load color table and color map presets from static header files
- Replace example images with `LCH` space versions
- Add CMakeLists `add_subdirectory()` dependency import as default for convenience

### Fixed
- Fix typo in `LCH` lerp shortest path


## [v1.1.1] - 2019-05-19

### Fixed
- Fix `LCH` interpolation after `HCL` re-work


## [v1.1.0] - 2019-05-19

### Added
- Add CMake support
- Add non-qt examples and explicit unit tests
- Add `RGB` gamma compounding
- Add `sRGB` linearization
- Add `Adobe RGB` conversions
- Add readme attributions
- Add explicit conversions unit tests

### Changed
- Replace `HCL` by `LCH` to disambiguate from `CIE L*C*h(uv)`

### Fixed
- Represent `LCH` values in degrees
- Fix `LCH` wrapping


## [v1.0.0] - 2019-05-17
Initial release.
