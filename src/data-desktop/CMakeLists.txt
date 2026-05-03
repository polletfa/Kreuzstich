# Kreuzstich
# Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
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

# Target: data-desktop
qt_add_library(data-desktop STATIC ${SOURCES})
set(CODEQL_CPP_TARGETS ${CODEQL_CPP_TARGETS} data-desktop PARENT_SCOPE)
target_link_libraries(data-desktop PUBLIC core)
target_link_libraries(data-desktop PUBLIC Qt6::Core Qt6::Gui)
target_include_directories(data-desktop PRIVATE ${core_INCLUDES})

# Export variables
set(data-desktop_INCLUDES ${CMAKE_SOURCE_DIR}/src PARENT_SCOPE)
