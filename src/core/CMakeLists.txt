# Kreuzstich
# Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
# MIT License, see LICENSE file.

# Sources

set(SOURCES
    Version.cpp
    ${CMAKE_BINARY_DIR}/generate_version/core/Version.hpp

    ColorSpace.hpp
    ColorSpace.cpp

    Thread.hpp
    Thread.cpp
    ThreadList.hpp
    ThreadList.cpp

    Selection.hpp
    Selection.cpp
    Pattern.hpp
    Pattern.cpp
)

# Resources
set(LICENSE_FILE ${CMAKE_SOURCE_DIR}/LICENSE)

# Version
if(NOT EMSCRIPTEN)
    include(generate_version)
    generate_version(${CMAKE_CURRENT_SOURCE_DIR}/Version.hpp.in ${CMAKE_BINARY_DIR}/generate_version/core/Version.hpp)
else()
    add_custom_command(
        OUTPUT ${CMAKE_BINARY_DIR}/generate_version/core/Version.hpp
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/../generate_version/core/Version.hpp
        ${CMAKE_BINARY_DIR}/generate_version/core/Version.hpp
    )
    add_custom_target(get_version_file DEPENDS ${CMAKE_BINARY_DIR}/generate_version/core/Version.hpp)
endif()

# Target: core
add_library(core STATIC ${SOURCES})
set(CODEQL_CPP_TARGETS ${CODEQL_CPP_TARGETS} core PARENT_SCOPE)
target_include_directories(core PRIVATE "${CMAKE_BINARY_DIR}/generate_version/core")

if(EMSCRIPTEN)
    add_dependencies(core get_version_file)
endif()

# Export variables
set(core_INCLUDES ${CMAKE_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/generate_version PARENT_SCOPE)
