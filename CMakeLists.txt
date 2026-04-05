cmake_minimum_required(VERSION 3.19)

project(kreuzstich VERSION 1.0 LANGUAGES CXX)

# Basic definitions

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Requirements

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

# Sources

set(PROJECT_SOURCES
    src/main.cpp
    src/version.cpp
    src/gui/MainWindow.cpp
    src/gui/MainWindow.hpp
    src/gui/MainWindow.ui
)

# Target: kreuzstich

qt_add_executable(kreuzstich
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)
set_target_properties(kreuzstich PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)
target_link_libraries(kreuzstich PRIVATE Qt6::Core Qt6::Widgets)

## Generate version.hpp
add_custom_target(generate_version ALL
    COMMAND ${CMAKE_COMMAND}
    -DSOURCE=${CMAKE_SOURCE_DIR}/src/version.hpp.in
    -DOUTPUT=${CMAKE_BINARY_DIR}/generate_version/version.hpp
    -DMAJOR=${PROJECT_VERSION_MAJOR}
    -DMINOR=${PROJECT_VERSION_MINOR}
    -DIS_RELEASE_BUILD=$<CONFIG:Release>
    -P ${CMAKE_SOURCE_DIR}/tools/generate_version.cmake
    COMMENT "Generating version.hpp"
)
target_include_directories(kreuzstich PRIVATE ${CMAKE_BINARY_DIR}/generate_version)
add_dependencies(kreuzstich generate_version)

## Generate colortables (external resource, but still a dependency)
add_subdirectory(resources/colortables)
add_dependencies(kreuzstich generate_colortables)

## Add translation files
add_subdirectory(resources/i18n)
target_link_libraries(kreuzstich PRIVATE i18n_resources)

## Install

include(GNUInstallDirs)
install(TARGETS kreuzstich
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
