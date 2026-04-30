# Kreuzstich
# Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
# MIT License, see LICENSE file.

# Requirements

find_package(Qt6 REQUIRED COMPONENTS Core Gui)

# Sources

set(SOURCES
    FileLocator.hpp
    FileLocator.cpp
    IQStandardPathsWrapper.hpp
    QStandardPathsWrapper.hpp
    QStandardPathsWrapper.cpp
    ThreadListParser.hpp
    ThreadListParser.cpp
    PictureFile.hpp
    PictureFile.cpp
)

# Target: data-qt
qt_add_library(data-qt STATIC ${SOURCES})
target_link_libraries(data-qt PUBLIC core)
target_link_libraries(data-qt PUBLIC Qt6::Core Qt6::Gui)
target_include_directories(data-qt PRIVATE ${core_INCLUDES})

# Export variables
set(data-qt_INCLUDES ${CMAKE_SOURCE_DIR}/src PARENT_SCOPE)
