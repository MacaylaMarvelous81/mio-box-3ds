# template

This is a template for starting new 3DS libctru projects.

## Build

Configure with CMake:

```sh
$DEVKITPRO/portlibs/3ds/bin/arm-none-eabi-cmake -B build/3ds -S .
```

`arm-none-eabi-cmake` is actually an alias-like script which invokes `cmake`
with `-DCMAKE_TOOLCHAIN_FILE=${DEVKITPRO}/cmake/3DS.cmake`, so you can also
just invoke `cmake` with that. Alternatively, use the `default` preset as
defined in `CMakePresets.json`.

```sh
cmake --preset default .
```
