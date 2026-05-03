# Kreuzstich
# Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
# MIT License, see LICENSE file.

cmake_minimum_required(VERSION 3.19)

project(Kreuzstich
    VERSION 1.0
    LANGUAGES CXX
    HOMEPAGE_URL "https://github.com/polletfa/Kreuzstich"
)

# Project-wide definitions: Cmake

if(NOT EMSCRIPTEN)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
    list(APPEND CMAKE_CTEST_ARGUMENTS "--output-on-failure")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/tools")
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/dist)

# Project-wide definitions: C++

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_definitions($<$<CONFIG:Debug>:DEBUG>)
add_compile_options($<$<CONFIG:Debug>:--coverage>)
add_compile_options($<$<CONFIG:Debug>:-O0>)
add_compile_options($<$<CONFIG:Debug>:-g>)
add_link_options($<$<CONFIG:Debug>:--coverage>)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

set(CODEQL_CPP_TARGETS "")

## Components (native + wasm builds)

add_subdirectory(src/core)
add_subdirectory(src/wrapper-wasm)

if(NOT EMSCRIPTEN)
    # Components (native build only)
    add_subdirectory(src/data-desktop)
    add_subdirectory(src/gui-desktop)
    add_subdirectory(src/gui-web)

    ## Components: additional resources
    add_subdirectory(resources/threadlists)

    ## Unit Tests
    enable_testing()
    add_subdirectory(tests)

    ## Install
    include(generate_version)
    generate_version(${CMAKE_SOURCE_DIR}/tools/VERSION.in ${CMAKE_BINARY_DIR}/VERSION)
    install(FILES ${CMAKE_BINARY_DIR}/VERSION DESTINATION .)
    install(FILES LICENSE DESTINATION .)

    ## For CodeQL we need a target to compile C++ components only
    add_custom_target(codeql-cpp-build)
    add_dependencies(codeql-cpp-build ${CODEQL_CPP_TARGETS})
endif()
