# Kreuzstich
# Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
# MIT License, see LICENSE file.

# Requirements

find_package(Qt6 REQUIRED COMPONENTS Core)

# Sources

set(SOURCES
    Mockup.hpp
    Mockup.cpp
)

# Resources

set(TEST_FILES ${CMAKE_SOURCE_DIR}/resources/test_files)

# Target: testbase
add_library(testbase STATIC ${SOURCES})
target_compile_definitions(testbase PRIVATE TEST_FILES="${TEST_FILES}")
target_link_libraries(testbase PRIVATE
    Qt::Core
    GTest::gtest
)
set(testbase_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)
