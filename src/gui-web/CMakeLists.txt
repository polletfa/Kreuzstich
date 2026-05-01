# Kreuzstich
# Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
# MIT License, see LICENSE file.

# Requirements

find_program(NPM npm REQUIRED)

# Resources

set(RESOURCES
    ${CMAKE_SOURCE_DIR}/resources/icons/favicon.ico
    ${wrapper-wasm_ASSETS}
)

# Target: gui-web-npminstall
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/node_modules/.package-lock.json
    COMMAND ${NPM} install
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/package.json
    COMMENT "Installing Angular dependencies..."
)
add_custom_target(gui-web-npminstall DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/node_modules/.package-lock.json)

# Target: gui-web-resources
add_custom_target(gui-web-resources
    COMMAND cmake -E make_directory ${CMAKE_CURRENT_SOURCE_DIR}/build/assets
    COMMAND cmake -E copy ${RESOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/build/assets/
    COMMENT "Copy resources"
)

# Target: gui-web-declarations
add_custom_target(gui-web-declarations
    COMMAND cmake -E make_directory ${CMAKE_CURRENT_SOURCE_DIR}/build/src
    COMMAND cmake -E copy ${wrapper-wasm_DECLARATIONS} ${CMAKE_CURRENT_SOURCE_DIR}/build/src/
    COMMENT "Copy resources"
)

# Target: gui-web
add_custom_target(gui-web ALL
    COMMAND ${NPM} run build-$<$<CONFIG:Debug>:dev>$<$<CONFIG:Release>:prod>
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Building Angular app..."
)
add_dependencies(gui-web gui-web-npminstall gui-web-resources gui-web-declarations)

# Target: gui-web-test
add_custom_target(gui-web-test
    COMMAND ${NPM} run test
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

# Target: gui-web-coverage
add_custom_target(gui-web-coverage
    COMMAND ${NPM} run coverage
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
