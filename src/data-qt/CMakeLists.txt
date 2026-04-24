# Kreuzstich
# Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
# MIT License, see LICENSE file.

# Requirements

find_package(Qt6 REQUIRED COMPONENTS Core)

# Sources

set(SOURCES
    FileLocator.hpp
    FileLocator.cpp
    IQStandardPathsWrapper.hpp
    QStandardPathsWrapper.hpp
    QStandardPathsWrapper.cpp
    ThreadListParser.hpp
    ThreadListParser.cpp
)

# Target: data-qt depends on core
qt_add_library(data-qt STATIC ${SOURCES})
target_link_libraries(data-qt PRIVATE core)
target_link_libraries(data-qt PRIVATE Qt6::Core)
target_include_directories(data-qt PRIVATE ${core_INCLUDES})

# Export variables
set(data-qt_INCLUDES ${CMAKE_SOURCE_DIR}/src PARENT_SCOPE)
