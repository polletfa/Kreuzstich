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

find_package(Qt6 REQUIRED COMPONENTS Core Widgets LinguistTools)

# Sources

set(PROJECT_SOURCES
#   C++ file                     Header file                   UI file
    src/main.cpp
    src/Version.cpp              src/Version.hpp
    src/gui/MainWindow.cpp       src/gui/MainWindow.hpp        src/gui/MainWindow.ui
    src/gui/AboutDialog.cpp      src/gui/AboutDialog.hpp       src/gui/AboutDialog.ui
)

set(TS_FILES
    resources/i18n/de_DE.ts
)

set(RESOURCES
#    resources/icons/icon512.png
#    resources/icons/icon256.png
    resources/icons/icon128.png
    resources/icons/icon64.png
#    resources/icons/icon32.png
)

set(LICENSE LICENSE)

# Target: kreuzstich

qt_add_executable(kreuzstich
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

## Generate version_defs.hpp
add_custom_target(generate_version ALL
    COMMAND ${CMAKE_COMMAND}
    -DSOURCE=${CMAKE_SOURCE_DIR}/src/version_defs.hpp.in
    -DOUTPUT=${CMAKE_BINARY_DIR}/generate_version/version_defs.hpp
    -DMAJOR=${PROJECT_VERSION_MAJOR}
    -DMINOR=${PROJECT_VERSION_MINOR}
    -DIS_RELEASE_BUILD=$<CONFIG:Release>
    -P ${CMAKE_SOURCE_DIR}/tools/generate_version.cmake
    COMMENT "Generating version_defs.hpp"
)
target_include_directories(kreuzstich PRIVATE ${CMAKE_BINARY_DIR}/generate_version)
add_dependencies(kreuzstich generate_version)

## Add translation files & other resources
qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/${TS_FILES}
#    OPTIONS -no-obsolete   # uncomment to "cleanup" the translation files by removing all unused strings
)
qt_add_resources(kreuzstich "i18n" PREFIX "/i18n" BASE ${CMAKE_BINARY_DIR} FILES ${QM_FILES})
qt_add_resources(kreuzstich "resources" PREFIX "/" BASE "resources/" FILES ${RESOURCES})
qt_add_resources(kreuzstich "LICENSE" PREFIX "/" FILES ${LICENSE})

## Generate colortables
add_subdirectory(resources/colortables)
add_dependencies(kreuzstich generate_colortables)

## Install

include(GNUInstallDirs)
install(TARGETS kreuzstich
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
