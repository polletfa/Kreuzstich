# Kreuzstich
# Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
# MIT License, see LICENSE file.

# Requirements

find_program(NPM npm REQUIRED)
if(WIN32)
    set(NPM_EXECUTABLE cmd /c "${NPM}")
else()
    set(NPM_EXECUTABLE "${NPM}")
endif()

# Target: wrapper-wasm-tests-npminstall
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/node_modules/.package-lock.json
    COMMAND ${NPM_EXECUTABLE} install
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
    COMMAND ${NPM_EXECUTABLE} run tsc   # check types before running tests
    COMMAND ${NPM_EXECUTABLE} run test
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/test-results
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/build/test-results/wrapper-wasm.xml ${CMAKE_BINARY_DIR}/test-results/wrapper-wasm.xml
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
add_dependencies(wrapper-wasm-tests wrapper-wasm-tests-npminstall wrapper-wasm-tests-wasm)

# Target: wrapper-wasm-tests-coverage
add_custom_target(wrapper-wasm-tests-coverage
    COMMAND ${NPM_EXECUTABLE} run coverage
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/coverage ${CMAKE_BINARY_DIR}/coverage_report/wrapper-wasm
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
add_dependencies(wrapper-wasm-tests-coverage wrapper-wasm-tests-npminstall wrapper-wasm-tests-wasm)

set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_CLEAN_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/node_modules/
    ${CMAKE_CURRENT_SOURCE_DIR}/build
    ${CMAKE_CURRENT_SOURCE_DIR}/coverage
)
