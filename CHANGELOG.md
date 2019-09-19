# Changelog
All notable changes to this project will be documented in this file.
The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/), and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).


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
