# Changelog
All notable changes to this project will be documented in this file.
The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/), and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).


## [unreleased]

## Added
- Add `Adobe RGB` conversions
- Add `RGB` gamma compounding
- Add `sRGB` linearization
- Add readme attributions
- Add explicit conversions unit tests

## Changed
- Replace `HCL` by `LCH` to disambiguate from `CIE L*C*h(uv)`

## Fixed
- Represent `LCH` values in degrees
- Fix `LCH` wrapping


## [v1.0.0] - 2019-05-17
Initial release.
