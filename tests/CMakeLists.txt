# Requirements

find_package(GTest REQUIRED)

# Sources

set(SOURCES
    creator/dummy.cpp
)

# Target: unittests

add_executable(unittests ${SOURCES})
target_include_directories(unittests PRIVATE ${common_INCLUDES} ${creator_INCLUDES} ${gui_INCLUDES})
target_link_libraries(unittests PRIVATE
    common creator gui
    GTest::gtest GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(unittests)
