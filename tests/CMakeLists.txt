# Kreuzstich
# Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
# MIT License, see LICENSE file.

# Requirements

include(FetchContent)
FetchContent_Declare(
    googletest
    DOWNLOAD_EXTRACT_TIMESTAMP true
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.tar.gz
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF)
FetchContent_MakeAvailable(googletest)

find_program(LCOV lcov)
if(LCOV STREQUAL LCOV-NOTFOUND)
    message(WARNING "Lcov not found!")
    set(SKIP_COVERAGE true)
else()
    message(STATUS "Found lcov: ${LCOV}")
endif()
find_program(GENHTML genhtml)
if(GENHTML STREQUAL GENHTML-NOTFOUND)
    message(WARNING "Genhtml not found!")
    set(SKIP_COVERAGE true)
else()
    message(STATUS "Found genhtml: ${GENHTML}")
endif()

# Subdirectories
add_subdirectory(testbase)
add_subdirectory(core)
add_subdirectory(data-desktop)
add_subdirectory(wrapper-wasm)

# Target: runtests
add_custom_target(runtests
    COMMAND ctest
    -j4
    --output-on-failure
    --output-junit ${CMAKE_BINARY_DIR}/test-results/cpp-components.xml
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
add_dependencies(runtests
    core-tests
    data-desktop-tests
    data-web-tests
    wrapper-wasm-tests
    gui-web-tests
)

# Target: coverage
if(SKIP_COVERAGE)
    message(WARNING "Skipping code coverage (missing requirement)")
else()
    add_custom_target(coverage
        COMMAND ${LCOV} --zerocounters --directory ${CMAKE_BINARY_DIR}
        COMMAND ctest -j4
        COMMAND ${LCOV} --capture --directory ${CMAKE_BINARY_DIR} --output-file coverage.info --ignore-errors inconsistent
        COMMAND ${LCOV} --remove coverage.info '/usr/*' '*/Qt*' '*/.qt/*' '*/tests/*' '*/gtest/*' '*/src/gtest*' --output-file coverage.info --ignore-errors inconsistent,unused
        COMMAND ${GENHTML} coverage.info --output-directory coverage_report/cpp-components
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
    add_dependencies(coverage
        core-tests
        data-desktop-tests
        data-web-tests-coverage
        wrapper-wasm-tests-coverage
        gui-web-tests-coverage
    )
endif()
