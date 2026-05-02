# Kreuzstich
# Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
# MIT License, see LICENSE file.

# Requirements

find_program(NPM npm REQUIRED)

# Target: wrapper-wasm-tests-npminstall
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/node_modules/.package-lock.json
    COMMAND ${NPM} install
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/package.json
    COMMENT "Installing dependencies..."
)
add_custom_target(wrapper-wasm-tests-npminstall DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/node_modules/.package-lock.json)

# Target: wrapper-wasm-tests-wasm
add_custom_target(wrapper-wasm-tests-wasm
    COMMAND cmake -E make_directory ${CMAKE_CURRENT_SOURCE_DIR}/build
    COMMAND cmake -E copy ${wrapper-wasm_ASSETS} ${wrapper-wasm_DECLARATIONS} ${CMAKE_CURRENT_SOURCE_DIR}/build
    COMMENT "Copy WASM files"
)
add_dependencies(wrapper-wasm-tests-wasm wrapper-wasm)

# Target: wrapper-wasm-tests
add_custom_target(wrapper-wasm-tests ALL
    COMMAND ${NPM} run test
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
add_dependencies(wrapper-wasm-tests wrapper-wasm-tests-npminstall wrapper-wasm-tests-wasm)

# Target: wrapper-wasm-coverage
add_custom_target(gui-web-coverage
    COMMAND ${NPM} run coverage
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
