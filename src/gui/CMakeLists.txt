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
    ${CMAKE_SOURCE_DIR}/resources/i18n/gui/de_DE.ts
)

# Target: gui depends on creator

qt_add_library(gui STATIC ${SOURCES})
target_link_libraries(gui PRIVATE creator)
target_link_libraries(gui PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)
target_include_directories(gui PRIVATE ${creator_INCLUDES})
qt_add_resources(gui "resources" PREFIX "/" BASE ${CMAKE_SOURCE_DIR}/resources/ FILES ${ICONS})
qt_add_translations(gui RESOURCE_PREFIX "/i18n/gui/" TS_FILES ${TRANSLATIONS}) # to cleanup, add: LUPDATE_OPTIONS -no-obsolete

# Target: kreuzstich depends on gui
qt_add_executable(kreuzstich ${ENTRYPOINT})
target_link_libraries(kreuzstich PRIVATE gui Qt6::Widgets)
target_include_directories(kreuzstich PRIVATE ${CMAKE_SOURCE_DIR}/src)
set_target_properties(kreuzstich PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Export variables
set(gui_INCLUDES ${CMAKE_SOURCE_DIR}/src PARENT_SCOPE)
