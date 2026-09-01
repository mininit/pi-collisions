# Pi Collisions

A small physics experiment simulating 1D elastic collisions between blocks, built with SDL3 and C++.

## Requirements

- CMake 3.22+
- A C++20 compiler
- SDL3

## Install SDL3 (macOS via Homebrew)

```sh
brew install sdl3
```

## Build

```sh
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
```

## Run

```sh
./build/blocks
```

## Project Structure

```
/
├── src/
│   ├── main.cpp
│   └── block.h
├── CMakeLists.txt
└── README.md
```
