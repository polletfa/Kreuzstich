# Kreuzstich
# Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
# MIT License, see LICENSE file.

# Requirements

find_package(GTest)
find_program(LCOV lcov)
find_program(GENHTML genhtml)

# Sources

set(SOURCES
    MockupBase.hpp
    MockupBase.cpp

    creator/utils/Version.cpp

    creator/colors/ColorSpace.cpp
    creator/colors/Thread.cpp

    creator/files/Mockup_QStandardPathsWrapper.hpp
    creator/files/Mockup_QStandardPathsWrapper.cpp
    creator/files/FileLocator.cpp
)

# Target: unittests depends on creator, gui
if(GTest_FOUND)
    add_executable(unittests ${SOURCES})
    target_compile_definitions(unittests PRIVATE TEST_FILES="${CMAKE_SOURCE_DIR}/resources/test_files")
    target_include_directories(unittests PRIVATE ${creator_INCLUDES} ${gui_INCLUDES})
    target_link_libraries(unittests PRIVATE
        creator gui
        GTest::gtest GTest::gtest_main
    )

    include(GoogleTest)
    gtest_discover_tests(unittests)
else()
    message(STATUS "GTest not found, skipping unittests")
endif()

if(LCOV AND GENHTML)
    add_custom_target(coverage
        COMMAND ${LCOV} --zerocounters --directory ${CMAKE_BINARY_DIR}
        COMMAND ctest --output-on-failure
        COMMAND ${LCOV} --capture --directory ${CMAKE_BINARY_DIR} --output-file coverage.info --ignore-errors inconsistent
        COMMAND ${LCOV} --remove coverage.info '/usr/*' '*/Qt*' '*/.qt/*' '*/tests/*' --output-file coverage.info --ignore-errors inconsistent,unused
        COMMAND ${GENHTML} coverage.info --output-directory coverage_report
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        DEPENDS unittests
    )
else()
    message(STATUS "lcov and/or genhtml not found, skipping code coverage")
endif()
