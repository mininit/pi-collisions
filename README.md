# Pi Collisions

A small physics experiment using **SDL3** and **C++** to simulate 1D elastic collisions between blocks.  
This project uses **CMake** for building and requires **SDL3** installed on your system.

## Requirements

- C++20 or later  
- CMake 3.22+  
- SDL3 (installed via Homebrew on macOS)

## Install SDL3 (Homebrew)

```sh
brew install sdl3
```

## Build

```sh
cmake -B build
cmake --build build
```

## Run the Program

```sh
cd build
./blocks
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
