cmake_minimum_required(VERSION 3.22)
project(blocks LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SDL3 CONFIG REQUIRED)

add_executable(blocks src/main.cpp)

target_compile_features(blocks PRIVATE cxx_std_20)
target_link_libraries(blocks PRIVATE SDL3::SDL3)
