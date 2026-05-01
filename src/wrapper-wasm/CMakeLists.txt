# Kreuzstich
# Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
# MIT License, see LICENSE file.

# Requirements

if(NOT DEFINED ENV{EMSDK})
    message(FATAL_ERROR "EMSDK not found. Please execute 'source emsdk_env.sh'.")
endif()

# Sources

set(SOURCES
    Version.cpp
)

set(NAMESPACES
    Version.namespace.js
)

set(DECLARATIONS
    Version.d.ts
    Core.d.ts
)

#

if(NOT EMSCRIPTEN)
    # Target: wrapper-wasm
    include(ExternalProject)
    ExternalProject_Add(wrapper-wasm
        SOURCE_DIR "${CMAKE_SOURCE_DIR}"
        BINARY_DIR "${CMAKE_BINARY_DIR}/wasm"
        CMAKE_ARGS
        -DCMAKE_TOOLCHAIN_FILE=$ENV{EMSDK}/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        BUILD_ALWAYS TRUE
        INSTALL_COMMAND ""
    )

    # Export variables
    set(wrapper-wasm_ASSETS ${CMAKE_BINARY_DIR}/wasm/core.wasm ${CMAKE_BINARY_DIR}/wasm/core.js PARENT_SCOPE)
    set(wrapper-wasm_DECLARATIONS ${CMAKE_BINARY_DIR}/wasm/core.d.ts PARENT_SCOPE)
else()
    # Target: wrapper-wasm-namespaces
    add_custom_target(wrapper-wasm-namespaces
        COMMAND ${CMAKE_COMMAND}
        -DSOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}
        -DINPUT="${NAMESPACES}"
        -DOUTPUT=${CMAKE_BINARY_DIR}/namespaces.js
        -P ${CMAKE_SOURCE_DIR}/tools/merge_files.cmake
        DEPENDS ${NAMESPACES}
        COMMENT "Generating namespaces.js"
    )

    # Target: wrapper-wasm-declarations
    add_custom_target(wrapper-wasm-declarations
        COMMAND ${CMAKE_COMMAND}
        -DSOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}
        -DINPUT="${DECLARATIONS}"
        -DOUTPUT=${CMAKE_BINARY_DIR}/core.d.ts
        -P ${CMAKE_SOURCE_DIR}/tools/merge_files.cmake
        DEPENDS ${DECLARATIONS}
        COMMENT "Generating core.d.ts"
    )

    # Target: wrapper-wasm
    add_executable(wrapper-wasm ${SOURCES})
    add_dependencies(wrapper-wasm wrapper-wasm-namespaces wrapper-wasm-declarations)
    target_include_directories(wrapper-wasm PRIVATE ${core_INCLUDES})
    target_link_libraries(wrapper-wasm PRIVATE core)

    target_link_options(wrapper-wasm PRIVATE
        --bind
        -sMODULARIZE=1
        -sEXPORT_NAME=CoreModule
        -sENVIRONMENT=web
        -sALLOW_MEMORY_GROWTH=1
        -sFILESYSTEM=0
        "SHELL:--post-js ${CMAKE_BINARY_DIR}/namespaces.js"

        $<$<CONFIG:Debug>:-sASSERTIONS=2>
        $<$<CONFIG:Debug>:-sSAFE_HEAP=1>
        $<$<CONFIG:Debug>:-g>

        $<$<CONFIG:Release>:-O3>
    )
    set_target_properties(wrapper-wasm PROPERTIES
        OUTPUT_NAME core
        SUFFIX ".js"
    )
endif()
