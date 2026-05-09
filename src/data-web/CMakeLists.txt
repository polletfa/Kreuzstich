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

# Version
include(generate_version)
generate_version(${CMAKE_CURRENT_SOURCE_DIR}/src/Version.ts.in ${CMAKE_CURRENT_SOURCE_DIR}/build/Version.ts)

# Target: data-web-npminstall
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/node_modules/.package-lock.json
    COMMAND ${NPM_EXECUTABLE} install
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/package.json
    COMMENT "Installing dependencies..."
)
add_custom_target(data-web-npminstall DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/node_modules/.package-lock.json)

# Target: data-web
add_custom_target(data-web ALL
    COMMAND ${NPM_EXECUTABLE} run build
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Building app..."
)
add_dependencies(data-web data-web-npminstall)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/dist/index.cjs DESTINATION data-web COMPONENT web-app)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/package.json DESTINATION data-web COMPONENT web-app)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/package-lock.json DESTINATION data-web COMPONENT web-app)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/resources/sql DESTINATION . COMPONENT web-app)
add_dependencies(install-web-app data-web)

# Target: data-web-tests
add_custom_target(data-web-tests
    COMMAND ${NPM_EXECUTABLE} run test
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/test-results
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/build/test-results/data-web.xml ${CMAKE_BINARY_DIR}/test-results/data-web.xml
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
add_dependencies(data-web-tests data-web-npminstall)

# Target: data-web-tests-coverage
add_custom_target(data-web-tests-coverage
    COMMAND ${NPM_EXECUTABLE} run coverage
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/coverage ${CMAKE_BINARY_DIR}/coverage_report/data-web
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
add_dependencies(data-web-tests-coverage data-web-npminstall)

set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_CLEAN_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/node_modules/
    ${CMAKE_CURRENT_SOURCE_DIR}/build/
    ${CMAKE_CURRENT_SOURCE_DIR}/coverage/
)
