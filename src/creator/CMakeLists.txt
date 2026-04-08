# Requirements

find_package(Qt6 REQUIRED COMPONENTS Core Gui LinguistTools)

# Sources

set(SOURCES
    # C++ file           Header file
    dummy.cpp            dummy.hpp
)

# Resources
set(TRANSLATIONS
    ${CMAKE_SOURCE_DIR}/resources/i18n/creator/de_DE.ts
)

# Target: version depends on generate_version
qt_add_library(creator STATIC ${SOURCES})
target_link_libraries(creator PRIVATE Qt6::Core Qt6::Gui)
qt_add_translations(creator RESOURCE_PREFIX "/i18n/creator/" TS_FILES ${TRANSLATIONS}) # to cleanup, add: LUPDATE_OPTIONS -no-obsolete

# Export variables
set(creator_INCLUDES ${CMAKE_SOURCE_DIR}/src PARENT_SCOPE)
