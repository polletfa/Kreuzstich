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
    ${CMAKE_SOURCE_DIR}/resources/i18n/gui-qt/de_DE.ts
)

# Target: gui-qt depends on core and data-qt
qt_add_library(gui-qt STATIC ${SOURCES})
set_target_properties(gui-qt PROPERTIES
    AUTOUIC ON
    AUTOMOC ON
    AUTORCC ON
)
target_link_libraries(gui-qt PUBLIC core data-qt)
target_link_libraries(gui-qt PUBLIC Qt6::Core Qt6::Gui Qt6::Widgets)
target_include_directories(gui-qt PRIVATE ${core_INCLUDES} ${data-qt_INCLUDES})
qt_add_resources(gui-qt "gui-qt_resources" PREFIX "/" BASE ${CMAKE_SOURCE_DIR}/resources/ FILES ${ICONS})
qt_create_translation(QM_FILES ${CMAKE_CURRENT_SOURCE_DIR} ${TRANSLATIONS}) # to cleanup, add: OPTIONS -no-obsolete
qt_add_resources(gui-qt "gui-qt_translations" PREFIX "/i18n/gui-qt" BASE ${CMAKE_CURRENT_BINARY_DIR} FILES ${QM_FILES})

# Target: kreuzstich depends on gui-qt
# (actually just qui-qt + main.cpp - separation required for unit tests)
qt_add_executable(kreuzstich ${ENTRYPOINT})
target_link_libraries(kreuzstich PUBLIC gui-qt Qt6::Widgets)
target_include_directories(kreuzstich PRIVATE ${CMAKE_SOURCE_DIR}/src)
set_target_properties(kreuzstich PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Export variables
set(gui-qt_INCLUDES ${CMAKE_SOURCE_DIR}/src PARENT_SCOPE)
