# SILO - Documentation
---
## Overview
This header-only library is designed with a single goal in mind. Make designing physics related functions easier and faster.  
The code is designed to allow for as much as possible of the calculation to be done at compile time.  
The header has a dedicated namespace, `SI::*`.

## Current Features
- Support for all the 7 fundamental SI units.
- Support for deriving units from fundamental units using standard arithmetic.
- Support for constexpr calculations of values.
- Compile time checking of unit correctness.

## Requirements
- Compiler with at least C++20 support.
