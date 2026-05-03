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
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${wrapper-wasm_DIR}/node ${CMAKE_CURRENT_SOURCE_DIR}/build/wrapper-wasm
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${wrapper-wasm_DIR}/lib ${CMAKE_CURRENT_SOURCE_DIR}/build/wrapper-wasm
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Copy wrapper-wasm"
)
add_dependencies(wrapper-wasm-tests-wasm wrapper-wasm)

# Target: wrapper-wasm-tests
add_custom_target(wrapper-wasm-tests
    COMMAND ${NPM} run tsc   # check types before running tests
    COMMAND ${NPM} run test
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/tests/wrapper-wasm/test-results/wrapper-wasm.xml ${CMAKE_BINARY_DIR}/test-results/
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
add_dependencies(wrapper-wasm-tests wrapper-wasm-tests-npminstall wrapper-wasm-tests-wasm)

# Target: wrapper-wasm-tests-coverage
add_custom_target(wrapper-wasm-tests-coverage
    COMMAND ${NPM} run coverage
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/tests/wrapper-wasm/coverage ${CMAKE_BINARY_DIR}/coverage_report/wrapper-wasm
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
add_dependencies(wrapper-wasm-tests-coverage wrapper-wasm-tests-npminstall wrapper-wasm-tests-wasm)

set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_CLEAN_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/node_modules/
    ${CMAKE_CURRENT_SOURCE_DIR}/build
    ${CMAKE_CURRENT_SOURCE_DIR}/coverage
)
