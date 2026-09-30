# Kreuzstich
# Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
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

string(TIMESTAMP BUILD_TIME "%Y-%m-%dT%H:%M:%SZ" UTC)

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

if(NOT EMSCRIPTEN)
    ## Install
    include(generate_version)
    generate_version(${CMAKE_SOURCE_DIR}/tools/VERSION.in ${CMAKE_BINARY_DIR}/VERSION)
    install(FILES ${CMAKE_BINARY_DIR}/VERSION DESTINATION . COMPONENT common)
    install(FILES ${CMAKE_SOURCE_DIR}/LICENSE DESTINATION . COMPONENT common)

    # Target: install-web-app
    add_custom_target(install-web-app
        COMMAND ${CMAKE_COMMAND} --install ${CMAKE_BINARY_DIR} --component common
        COMMAND ${CMAKE_COMMAND} --install ${CMAKE_BINARY_DIR} --component web-app
    )

    # Target: install-desktop-app
    add_custom_target(install-desktop-app
        COMMAND ${CMAKE_COMMAND} --install ${CMAKE_BINARY_DIR} --component common
        COMMAND ${CMAKE_COMMAND} --install ${CMAKE_BINARY_DIR} --component desktop-app
    )
endif()

## WASM build only
if(EMSCRIPTEN)
    add_subdirectory(src/core)
    add_subdirectory(src/wrapper-wasm)

## Standard build
else()
    # Components
    add_subdirectory(src/core)
    add_subdirectory(src/wrapper-wasm)
    add_subdirectory(src/data-desktop)
    add_subdirectory(src/data-web)
    add_subdirectory(src/gui-desktop)
    add_subdirectory(src/gui-web)

    ## Components: additional resources
    add_subdirectory(resources/threadlists)

    ## Unit Tests
    enable_testing()
    add_subdirectory(tests)

    ## Build C++ components only
    add_custom_target(build-cpp)
    add_dependencies(build-cpp
        core
        wrapper-wasm
        data-desktop
        gui-desktop
    )

    ## Build native components only
    add_custom_target(build-native)
    add_dependencies(build-native
        core
        data-desktop
        gui-desktop
    )

    ## Build web components only
    add_custom_target(build-web)
    add_dependencies(build-web
        wrapper-wasm
        data-web
        gui-web
    )

endif()
