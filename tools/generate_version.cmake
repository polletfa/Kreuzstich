# Kreuzstich
# Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
# MIT License, see LICENSE file.

function(generate_version INPUT OUTPUT)
    message(STATUS "Generating ${OUTPUT}")

    # LICENSE
    file(READ ${CMAKE_SOURCE_DIR}/LICENSE LICENSE)

    # LICENSE_SHORT
    file(STRINGS ${CMAKE_SOURCE_DIR}/LICENSE LINES LIMIT_COUNT 3)
    list(GET LINES 0 LICENSE_SHORT)
    list(GET LINES 2 COPYRIGHT)

    # GIT_COMMIT
    execute_process(COMMAND git rev-parse HEAD OUTPUT_VARIABLE GIT_COMMIT OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET)
    execute_process(COMMAND git status --porcelain OUTPUT_VARIABLE GIT_PORCELAIN OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET)
    if(NOT GIT_PORCELAIN STREQUAL "")
        unset(GIT_COMMIT)
    endif()

    # Configure
    configure_file(${INPUT} ${OUTPUT} @ONLY)
endfunction()
