# Requirements

find_program(IMAGEMAGICK_CONVERT convert)
if(NOT IMAGEMAGICK_CONVERT)
    message(FATAL_ERROR "ImageMagick convert not found. Install with: sudo apt install imagemagick (Debian/Ubuntu)")
endif()
message(STATUS "Found ImageMagick convert: ${IMAGEMAGICK_CONVERT}")

find_program(BASH bash)
if(NOT BASH)
    message(FATAL_ERROR "Bash not found. Install with: sudo apt install bash (Debian/Ubuntu)")
endif()
message(STATUS "Found bash: ${BASH}")

# Sources

set(THREADLISTS dmc)
set(THREADLISTS_SOURCES_dmc
    01.def 02.def 03.def 04.def 05.def 06.def 07.def 08.def 09.def 10.def
    11.def 12.def 13.def 14.def 15.def 16.def 17.def 18.def 19.def
    Page1.jpg  Page2.jpg  Page3.jpg Page4.jpg
    README
)
set(THREADLISTS_NAME_dmc DMC)

# Target: threadlists

set(THREADLIST_FILES)
foreach(NAME ${THREADLISTS})
    set(SOURCES)
    foreach(SRC ${THREADLISTS_SOURCES_${NAME}})
        list(APPEND SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${NAME}/${SRC})
    endforeach()
    set(INTERMEDIATE ${CMAKE_BINARY_DIR}/generate_threadlists/${NAME})
    set(OUTPUT ${CMAKE_BINARY_DIR}/threadlists/${NAME}.threads)
    add_custom_command(
        OUTPUT ${OUTPUT}
        COMMAND ${CMAKE_SOURCE_DIR}/tools/generate_threadlist.sh
                ${THREADLISTS_NAME_${NAME}} ${CMAKE_CURRENT_SOURCE_DIR}/${NAME} ${INTERMEDIATE} ${OUTPUT}
        DEPENDS ${SOURCES}
        COMMENT "Generating ${NAME}.threads"
    )
    list(APPEND THREADLISTS_FILES ${OUTPUT})
endforeach()
add_custom_target(threadlists ALL DEPENDS ${THREADLISTS_FILES}
    COMMENT "Building threadlists"
)
