# C++23 Standard Library Modules Example

This project demonstrates how to use C++23's `import std;` feature with CMake.

## Prerequisites

To build this project, you need a compiler that supports C++23 Standard Library Modules:
- **Clang 17+** (Upstream LLVM, not Apple Clang)
- **GCC 14+**
- **CMake 3.30+**

## The "Magic" in CMakeLists.txt

The line:
```cmake
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")
```
is required because support for `import std;` is still experimental in CMake. This UUID is a "gatekeeper" hash that acknowledges you are using an unstable feature. It may change in future CMake versions.

## Building on macOS

Apple Clang (the default `clang++` on macOS) does **not** fully support `import std;` yet. You need to install upstream LLVM:

```bash
brew install llvm
```

Then build with the specific compiler:

```bash
# Point to the Homebrew LLVM clang++
export CXX=$(brew --prefix llvm)/bin/clang++
cmake -S . -B build
cmake --build build
./build/main
```
