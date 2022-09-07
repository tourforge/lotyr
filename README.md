# Lotyr
A library that wraps Valhalla with a tiny bit of code to make it easy to embed
in your own application written in any language.

Lotyr (**Lo**cal wrapper around Valhalla's **Tyr**) produces a shared library
that can be used from nearly any programming language.

## Building
It's sufficient to set up your build environment as required by [Valhalla](https://github.com/valhalla/valhalla).
Soon, we will give more specific environment setup instructions for Lotyr, since it
needs fewer external dependencies than a typical full Valhalla build.

### Linux
```sh
cmake -B build -DCMAKE_BUILD_TYPE=Release
make -C build
```
NOTE: right now Valhalla fails to build with the latest GCC 12.2. Just use Clang
or an older version of GCC. If you don't want to uninstall GCC 12, you can manually
force a specific compiler binary to be executed like so:
```sh
export CC=clang
export CXX=clang++
```

### MacOS
```sh
cmake -B build -DCMAKE_BUILD_TYPE=Release
make -C build -j$(sysctl -n hw.physicalcpu)
```

### Windows
Windows builds are supported but we still need to give precise instructions.
