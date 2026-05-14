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

# Resources

set(RESOURCES
    ${CMAKE_SOURCE_DIR}/resources/icons/favicon.ico
)

# Version
include(generate_version)
generate_version(${CMAKE_CURRENT_SOURCE_DIR}/src/app/constants/version.constants.ts.in ${CMAKE_CURRENT_SOURCE_DIR}/build/version.constants.ts)

# Target: gui-web-npminstall
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/node_modules/.package-lock.json
    COMMAND ${NPM_EXECUTABLE} install
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/package.json
    COMMENT "Installing Angular dependencies..."
)
add_custom_target(gui-web-npminstall DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/node_modules/.package-lock.json)

# Target: gui-web-resources
add_custom_target(gui-web-resources
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_SOURCE_DIR}/build/assets
    COMMAND ${CMAKE_COMMAND} -E copy ${RESOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/build/assets/
    COMMENT "Copy resources"
)

# Target: gui-web-wasm
add_custom_target(gui-web-wasm
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_SOURCE_DIR}/build
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${wrapper-wasm_DIR}/web ${CMAKE_CURRENT_SOURCE_DIR}/build/wrapper-wasm
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${wrapper-wasm_DIR}/lib ${CMAKE_CURRENT_SOURCE_DIR}/build/wrapper-wasm
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Copy wrapper-wasm"
)
add_dependencies(gui-web-wasm wrapper-wasm)

# Target: gui-web
add_custom_target(gui-web ALL
    COMMAND ${NPM_EXECUTABLE} run build-$<$<CONFIG:Debug>:debug>$<$<CONFIG:Release>:release>
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Building Angular app..."
)
add_dependencies(gui-web gui-web-npminstall gui-web-resources gui-web-wasm data-web) # Note: also requires data-web, because it imports files from there
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/dist/gui-web/ DESTINATION gui-web COMPONENT web-app)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/resources/docker DESTINATION . COMPONENT web-app)
add_dependencies(install-web-app gui-web)

# Target: gui-web-tests
add_custom_target(gui-web-tests
    COMMAND ${NPM_EXECUTABLE} run test
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/test-results
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/build/test-results/gui-web.xml ${CMAKE_BINARY_DIR}/test-results/gui-web.xml
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
add_dependencies(gui-web-tests gui-web-npminstall gui-web-resources gui-web-wasm)

# Target: gui-web-tests-coverage
add_custom_target(gui-web-tests-coverage
    COMMAND ${NPM_EXECUTABLE} run coverage
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/coverage/gui-web ${CMAKE_BINARY_DIR}/coverage_report/gui-web
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
add_dependencies(gui-web-tests-coverage gui-web-npminstall gui-web-resources gui-web-wasm)

set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_CLEAN_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/node_modules/
    ${CMAKE_CURRENT_SOURCE_DIR}/build/
    ${CMAKE_CURRENT_SOURCE_DIR}/dist/
    ${CMAKE_CURRENT_SOURCE_DIR}/coverage/
)
