# Kreuzstich
# Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
# MIT License, see LICENSE file.

# Requirements

if(NOT DEFINED ENV{EMSDK})
    message(FATAL_ERROR "EMSDK not found. Please execute 'source emsdk_env.sh'.")
endif()

# Sources

set(SOURCES
    Version.bindings.cpp
    ColorSpace.bindings.cpp
    Thread.bindings.cpp
    ThreadList.bindings.cpp
)

set(LIB_SOURCES
    index.ts
    Version.ts
    ColorSpace.ts
    Thread.ts
    ThreadList.ts
)

#

if(NOT EMSCRIPTEN)
    # Target: wrapper-wasm
    include(ExternalProject)
    if(WIN32)
        set(WASM_GENERATOR "Ninja")
    else()
        set(WASM_GENERATOR "Unix Makefiles")
    endif()
    ExternalProject_Add(wrapper-wasm
        SOURCE_DIR "${CMAKE_SOURCE_DIR}"
        BINARY_DIR "${CMAKE_BINARY_DIR}/wasm"
        CMAKE_GENERATOR "${WASM_GENERATOR}"
        CMAKE_ARGS
        -DCMAKE_TOOLCHAIN_FILE=$ENV{EMSDK}/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        BUILD_ALWAYS TRUE
    )
    set(CODEQL_CPP_TARGETS ${CODEQL_CPP_TARGETS} wrapper-wasm PARENT_SCOPE)

    # Export variables
    set(wrapper-wasm_DIR ${CMAKE_BINARY_DIR}/wasm/dist PARENT_SCOPE)
else()
    function(add_wasm_target TARGET_NAME ENVIRONMENT)
        add_executable(${TARGET_NAME} ${SOURCES})
        target_include_directories(${TARGET_NAME} PRIVATE ${core_INCLUDES})
        target_link_libraries(${TARGET_NAME} PRIVATE core)

        target_link_options(${TARGET_NAME} PRIVATE
            --bind
            -sMODULARIZE=1
            -sENVIRONMENT=${ENVIRONMENT}
            -sALLOW_MEMORY_GROWTH=1
            -sFILESYSTEM=0
            "SHELL:--emit-tsd ${CMAKE_BINARY_DIR}/wrapper-wasm.d.ts"

            $<$<CONFIG:Debug>:-sASSERTIONS=2>
            $<$<CONFIG:Debug>:-sSAFE_HEAP=1>
            $<$<CONFIG:Debug>:-g>
            $<$<CONFIG:Debug>:-fexceptions>
            $<$<CONFIG:Debug>:-sEXCEPTION_CATCHING_ALLOWED=all>

            $<$<CONFIG:Release>:-O3>
        )
        set_target_properties(${TARGET_NAME} PROPERTIES
            SUFFIX ".js"
            OUTPUT_NAME wrapper-wasm
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${ENVIRONMENT}
        )
    endfunction()

    # Target: wrapper-wasm-node
    add_wasm_target(wrapper-wasm-node node)

    # Target: wrapper-wasm-web
    add_wasm_target(wrapper-wasm-web web)

    # Target: wrapper-wasm
    add_custom_target(wrapper-wasm)
    add_dependencies(wrapper-wasm wrapper-wasm-node wrapper-wasm-web)

    install(DIRECTORY ${CMAKE_BINARY_DIR}/node DESTINATION .)
    install(DIRECTORY ${CMAKE_BINARY_DIR}/web DESTINATION .)
    install(FILES ${LIB_SOURCES} ${CMAKE_BINARY_DIR}/wrapper-wasm.d.ts DESTINATION lib)
endif()
