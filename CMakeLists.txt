# Kreuzstich
# Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
# MIT License, see LICENSE file.

cmake_minimum_required(VERSION 3.19)

project(kreuzstich VERSION 1.0 LANGUAGES CXX)

# Basic definitions
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_compile_definitions($<$<CONFIG:Debug>:DEBUG>)
add_compile_options($<$<CONFIG:Debug>:--coverage>)
add_compile_options($<$<CONFIG:Debug>:-O0>)
add_compile_options($<$<CONFIG:Debug>:-g>)
add_link_options($<$<CONFIG:Debug>:--coverage>)

list(APPEND CMAKE_CTEST_ARGUMENTS "--output-on-failure")

## Components
add_subdirectory(src/creator)    # The actual logic (the "backend" so to speak)
add_subdirectory(src/gui)        # Standard desktop application

## Components: additional resources
add_subdirectory(resources/threadlists)

## Unit Tests
enable_testing()
add_subdirectory(tests)
