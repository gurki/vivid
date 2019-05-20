# Changelog
All notable changes to this project will be documented in this file.
The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/), and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).


## [v1.1.2] - 2019-05-20

## Changed
- Load color table and color map presets from static header files

## Fixed
- Fix typo in `LCH` lerp shortest path


## [v1.1.1] - 2019-05-19

## Fixed
- Fix `LCH` interpolation after `HCL` re-work


## [v1.1.0] - 2019-05-19

## Added
- Add CMake support
- Add non-qt examples and explicit unit tests
- Add `RGB` gamma compounding
- Add `sRGB` linearization
- Add `Adobe RGB` conversions
- Add readme attributions
- Add explicit conversions unit tests

## Changed
- Replace `HCL` by `LCH` to disambiguate from `CIE L*C*h(uv)`

## Fixed
- Represent `LCH` values in degrees
- Fix `LCH` wrapping


## [v1.0.0] - 2019-05-17
Initial release.
