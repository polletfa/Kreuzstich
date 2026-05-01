# Kreuzstich
# Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
# MIT License, see LICENSE file.

cmake_minimum_required(VERSION 3.19)

project(kreuzstich VERSION 1.0 LANGUAGES CXX)

# Basic definitions
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT EMSCRIPTEN)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_compile_definitions($<$<CONFIG:Debug>:DEBUG>)
add_compile_options($<$<CONFIG:Debug>:--coverage>)
add_compile_options($<$<CONFIG:Debug>:-O0>)
add_compile_options($<$<CONFIG:Debug>:-g>)
add_link_options($<$<CONFIG:Debug>:--coverage>)

list(APPEND CMAKE_CTEST_ARGUMENTS "--output-on-failure")

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

## Components
add_subdirectory(src/core)
add_subdirectory(src/wrapper-wasm)
if(NOT EMSCRIPTEN)
    add_subdirectory(src/data-desktop)
    add_subdirectory(src/gui-desktop)
    add_subdirectory(src/gui-web)
endif()

## Components: additional resources
if(NOT EMSCRIPTEN)
    add_subdirectory(resources/threadlists)
endif()

## Unit Tests
if(NOT EMSCRIPTEN)
    enable_testing()
    add_subdirectory(tests)
endif()
