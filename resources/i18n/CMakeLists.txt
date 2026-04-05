# Requirements

find_package(Qt6 REQUIRED COMPONENTS LinguistTools)

# Sources

set(TS_FILES
    de_DE.ts
)

# Target: i18n_resources
set_source_files_properties(${TS_FILES}
    PROPERTIES OUTPUT_LOCATION
    ${CMAKE_BINARY_DIR}
)
qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR}/src ${TS_FILES} OPTIONS -no-obsolete)
add_library(i18n_resources STATIC)
qt_add_resources(i18n_resources "i18n" PREFIX "/i18n" BASE ${CMAKE_BINARY_DIR} FILES ${QM_FILES})
