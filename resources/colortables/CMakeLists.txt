# Requirements

find_program(IMAGEMAGICK_CONVERT convert)
if(NOT IMAGEMAGICK_CONVERT)
    message(FATAL_ERROR "ImageMagick convert not found. Install with: sudo apt install imagemagick (Debian/Ubuntu)")
endif()
message(STATUS "Found ImageMagick convert: ${IMAGEMAGICK_CONVERT}")

# Sources

set(COLORTABLES dmc)
set(COLORTABLES_SOURCES_dmc
    01.def 02.def 03.def 04.def 05.def 06.def 07.def 08.def 09.def 10.def
    11.def 12.def 13.def 14.def 15.def 16.def 17.def 18.def 19.def
    Page1.jpg  Page2.jpg  Page3.jpg Page4.jpg
    README
)
set(COLORTABLES_NAME_dmc DMC)

# Target: generate_colortables

set(COLORTABLE_FILES)
foreach(NAME ${COLORTABLES})
    set(SOURCES)
    foreach(SRC ${COLORTABLES_SOURCES_${NAME}})
        list(APPEND SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${NAME}/${SRC})
    endforeach()
    set(INTERMEDIATE ${CMAKE_BINARY_DIR}/generate_colortables/${NAME})
    set(OUTPUT ${CMAKE_BINARY_DIR}/colortables/${NAME}.colors)
    add_custom_command(
        OUTPUT ${OUTPUT}
        COMMAND ${CMAKE_SOURCE_DIR}/tools/generate_colortable.sh
        ${COLORTABLES_NAME_${NAME}} ${CMAKE_CURRENT_SOURCE_DIR}/${NAME} ${INTERMEDIATE} ${OUTPUT}
        DEPENDS ${SOURCES}
        COMMENT "Generating ${NAME}.colors"
    )
    list(APPEND COLORTABLES_FILES ${OUTPUT})
endforeach()
add_custom_target(generate_colortables ALL DEPENDS ${COLORTABLES_FILES}
    COMMENT "Building colortables"
)
