# Math library - Fractions

*MIND THE DOCS!*

*Created by Ondrej Nedojedly at 13.03.2023 (dd/mm/yyyy).*
## About
This library supports (Not yet) basic and advanced fraction operations for extended use-cases. Witten in obsolete [C99 standard]() and build with [CMake]() toolset.

## Naming conventions
* `a` - numenator
* `b` - denumenator

* `fracXXXXXX` for library namespace, every function, struct etc. stars with this namespace.

## API
### Fraction component
* `fracFractionXX` is fraction component itself (struct). Other XX's are for to specify the data type. Supported data types are the following:
  * `64` - 64-bit integer.
  * other DT may become supported in the future.

### Creation of compont
Component may be created in two different functions.
* By copying
* By direct creation

### Setters
* `fracSetXXXX` is used when data in `fracFraction` are required to be changed. It is recommended to use a `Set` function when fraction data is required to be changed. Changing data directly, is considered to be a bad practice. Every `Set`function has as its first parameter pointer to the fraction component.
  * `fracSet[TYPE]` functions that are used to set `a` and `b` in fraction component. `[TYPE]` specifies to which this function applies to. f.e.: `fracSetFraction64(Fraction64* adr, int64_t a, int64_t b)`.
  * `fracSetA[TYPE]` same as `fracSet[TYPE]`, but changes data only in `a` instead of both.
  * `fracSetB[TYPE]` smae as `fracSet[TYPE]`, but changes data only in `b` instead of both.

## Build

### Supported compilers
* Apple clang version 14.0.0 (clang-1400.0.29.202)


