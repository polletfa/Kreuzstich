cmake_minimum_required(VERSION 3.16)

project(kreuzstich VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets LinguistTools)

set(TS_FILES resources/i18n/de_DE.ts)

set(PROJECT_SOURCES
    src/main.cpp
    src/gui/MainWindow.cpp
    src/gui/MainWindow.hpp
    src/gui/MainWindow.ui
    ${TS_FILES}
)

qt_add_executable(kreuzstich
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR}/src ${TS_FILES} OPTIONS -no-obsolete)
qt_add_resources(kreuzstich "i18n" PREFIX "/i18n" BASE ${CMAKE_BINARY_DIR} FILES ${QM_FILES})

target_link_libraries(kreuzstich PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(kreuzstich PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS kreuzstich
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_finalize_executable(kreuzstich)
