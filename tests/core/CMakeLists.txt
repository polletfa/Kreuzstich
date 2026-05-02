# Kreuzstich
# Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
# MIT License, see LICENSE file.

# Sources

set(SOURCES
    Version.test.cpp
    ColorSpace.test.cpp
    Thread.test.cpp
    ThreadList.test.cpp
    Selection.test.cpp
    Pattern.test.cpp
)

# Target: unittests
add_executable(core-tests ${SOURCES})
target_include_directories(core-tests PRIVATE ${testbase_INCLUDES} ${core_INCLUDES} ${data-desktop_INCLUDES}) # we use data-desktop to load test data
target_link_libraries(core-tests PRIVATE
    testbase core data-desktop
    GTest::gtest GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(core-tests
    PROPERTIES ENVIRONMENT "GTEST_OUTPUT=xml:${CMAKE_BINARY_DIR}/test-results/core.xml"
)
