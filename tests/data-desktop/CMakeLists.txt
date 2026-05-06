# Kreuzstich
# Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
# MIT License, see LICENSE file.

# Sources

set(SOURCES
     QStandardPathsWrapper.mock.hpp
     QStandardPathsWrapper.mock.cpp

     FileLocator.test.cpp
     ThreadListParser.test.cpp
     PictureFile.test.cpp
)

# Target: unittests
add_executable(data-desktop-tests ${SOURCES})
target_include_directories(data-desktop-tests PRIVATE ${testbase_INCLUDES} ${data-desktop_INCLUDES})
target_link_libraries(data-desktop-tests PRIVATE
    testbase data-desktop
    GTest::gtest GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(data-desktop-tests)
