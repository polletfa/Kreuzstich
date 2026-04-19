# Kreuzstich
# Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
# MIT License, see LICENSE file.

# Requirements

include(FetchContent)
FetchContent_Declare(
    googletest
    DOWNLOAD_EXTRACT_TIMESTAMP true
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.tar.gz
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

find_program(LCOV lcov)
if(LCOV STREQUAL LCOV-NOTFOUND)
    message(WARNING "Lcov not found!")
    set(SKIP_COVERAGE true)
else()
    message(STATUS "Found lcov: ${LCOV}")
endif()
find_program(GENHTML genhtml)
if(GENHTML STREQUAL GENHTML-NOTFOUND)
    message(WARNING "Genhtml not found!")
    set(SKIP_COVERAGE true)
else()
    message(STATUS "Found genhtml: ${GENHTML}")
endif()

# Suppress Qt AUTOMOC warning for googletest targets
foreach(target gtest gtest_main gmock gmock_main)
  if(TARGET ${target})
    set_target_properties(${target} PROPERTIES
      AUTOMOC OFF
      AUTOUIC OFF
      AUTORCC OFF
    )
  endif()
endforeach()

# Sources

set(SOURCES
    MockupBase.hpp
    MockupBase.cpp

    creator/utils/Version.cpp

    creator/colors/ColorSpace.cpp
    creator/colors/Thread.cpp

    creator/files/Mockup_QStandardPathsWrapper.hpp
    creator/files/Mockup_QStandardPathsWrapper.cpp
    creator/files/FileLocator.cpp
)

# Target: unittests depends on creator, gui
add_executable(unittests ${SOURCES})
target_compile_definitions(unittests PRIVATE TEST_FILES="${CMAKE_SOURCE_DIR}/resources/test_files")
target_include_directories(unittests PRIVATE ${creator_INCLUDES} ${gui_INCLUDES})
target_link_libraries(unittests PRIVATE
    creator gui
    GTest::gtest GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(unittests)

if(SKIP_COVERAGE)
    message(WARNING "Skipping code covereage (missing requirement)")
else()
    add_custom_target(coverage
        COMMAND ${LCOV} --zerocounters --directory ${CMAKE_BINARY_DIR}
        COMMAND ctest --output-on-failure
        COMMAND ${LCOV} --capture --directory ${CMAKE_BINARY_DIR} --output-file coverage.info --ignore-errors inconsistent
        COMMAND ${LCOV} --remove coverage.info '/usr/*' '*/Qt*' '*/.qt/*' '*/tests/*' '*/gtest/*' '*/src/gtest*' --output-file coverage.info --ignore-errors inconsistent,unused
        COMMAND ${GENHTML} coverage.info --output-directory coverage_report
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        DEPENDS unittests
    )
endif()
