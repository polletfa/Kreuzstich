string(TIMESTAMP BUILD_TIME "%s")
execute_process(COMMAND git rev-parse HEAD OUTPUT_VARIABLE GIT_COMMIT OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND git status --porcelain OUTPUT_VARIABLE GIT_PORCELAIN OUTPUT_STRIP_TRAILING_WHITESPACE)

if(GIT_PORCELAIN)
    set(GIT_DIRTY "true")
else()
    set(GIT_DIRTY "false")
endif()

if(NOT GIT_COMMIT)
    set(GIT_COMMIT "unknown")
endif()

if(IS_RELEASE_BUILD)
    set(RELEASE_BUILD "true")
else()
    set(RELEASE_BUILD "false")
endif()

configure_file(${SOURCE} ${OUTPUT} @ONLY)
