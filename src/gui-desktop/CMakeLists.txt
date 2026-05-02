# Kreuzstich
# Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
# MIT License, see LICENSE file.

# Requirements

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets LinguistTools)

# Sources

set(ENTRYPOINT
    main.cpp
)
set(SOURCES
    # C++ file           Header file           UI file
    Application.cpp      Application.hpp
    MainWindow.cpp       MainWindow.hpp        MainWindow.ui
    AboutDialog.cpp      AboutDialog.hpp       AboutDialog.ui
)

# Resources
set(ICONS
    ${CMAKE_SOURCE_DIR}/resources/icons/icon128.png
    ${CMAKE_SOURCE_DIR}/resources/icons/icon64.png
)
set(TRANSLATIONS
    ${CMAKE_SOURCE_DIR}/resources/i18n/gui-desktop/de_DE.ts
)

# Target: gui-desktop
qt_add_library(gui-desktop STATIC ${SOURCES})
set_target_properties(gui-desktop PROPERTIES
    AUTOUIC ON
    AUTOMOC ON
    AUTORCC ON
)
target_link_libraries(gui-desktop PUBLIC core data-desktop)
target_link_libraries(gui-desktop PUBLIC Qt6::Core Qt6::Gui Qt6::Widgets)
target_include_directories(gui-desktop PRIVATE ${core_INCLUDES} ${data-desktop_INCLUDES})
qt_add_resources(gui-desktop "gui-desktop_resources" PREFIX "/" BASE ${CMAKE_SOURCE_DIR}/resources/ FILES ${ICONS})
qt_create_translation(QM_FILES ${CMAKE_CURRENT_SOURCE_DIR} ${TRANSLATIONS}) # to cleanup, add: OPTIONS -no-obsolete
qt_add_resources(gui-desktop "gui-desktop_translations" PREFIX "/i18n/gui-desktop" BASE ${CMAKE_CURRENT_BINARY_DIR} FILES ${QM_FILES})

# Target: gui-desktop-executable
# (actually just qui-desktop + main.cpp - separation required for unit tests)
qt_add_executable(gui-desktop-executable ${ENTRYPOINT})
set(CODEQL_CPP_TARGETS ${CODEQL_CPP_TARGETS} gui-desktop-executable PARENT_SCOPE)
target_link_libraries(gui-desktop-executable PUBLIC gui-desktop Qt6::Widgets)
set_target_properties(gui-desktop-executable PROPERTIES
    OUTPUT_NAME kreuzstich
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)
install(TARGETS gui-desktop-executable
    RUNTIME DESTINATION gui-desktop
    BUNDLE DESTINATION gui-desktop
)

# Export variables
set(gui-desktop_INCLUDES ${CMAKE_SOURCE_DIR}/src PARENT_SCOPE)
