# Requirements

find_package(GTest)
find_program(LCOV lcov)
find_program(GENHTML genhtml)

# Sources

set(SOURCES
    creator/ColorSpace.cpp
    creator/Thread.cpp
)

# Target: unittests
if(GTest_FOUND)
    add_executable(unittests ${SOURCES})
    target_include_directories(unittests PRIVATE ${common_INCLUDES} ${creator_INCLUDES} ${gui_INCLUDES})
    target_link_libraries(unittests PRIVATE
        common creator gui
        GTest::gtest GTest::gtest_main
    )

    include(GoogleTest)
    gtest_discover_tests(unittests)
else()
    message(STATUS "GTest not found, skipping unittests")
endif()

if(LCOV AND GENHTML)
    add_custom_target(coverage
        COMMAND ${LCOV} --zerocounters --directory ${CMAKE_BINARY_DIR}
        COMMAND ctest --output-on-failure
        COMMAND ${LCOV} --capture --directory ${CMAKE_BINARY_DIR} --output-file coverage.info --ignore-errors inconsistent
        COMMAND ${LCOV} --remove coverage.info '/usr/*' '*/Qt*' '*/.qt/*' '*/tests/*' --output-file coverage.info --ignore-errors inconsistent,unused
        COMMAND ${GENHTML} coverage.info --output-directory coverage_report
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        DEPENDS unittests
    )
else()
    message(STATUS "lcov and/or genhtml not found, skipping code coverage")
endif()
