cmake_minimum_required(VERSION 2.8.11)

add_definitions(-DLAB_LIGHT=65 -DLAB_ANGLE=2)

add_definitions(-DPROJECT_NAME="libkreuzstich"
                -DMAJOR_VERSION=0
                -DMINOR_VERSION=1)

include_directories(/usr/include
                    /usr/local/include
                    ${ImageMagick_INCLUDE_DIRS}
                    ${LIBXML2_INCLUDE_DIR}
                    ${Boost_INCLUDE_DIRS})

set(SOURCES
    creator.cpp
    report.cpp
    resources.cpp
    thread.cpp
    units.cpp
    exceptions.cpp
    kreuzstich/creator.h
    kreuzstich/report.h
    kreuzstich/resources.h
    kreuzstich/thread.h
    kreuzstich/units.h
    kreuzstich/exceptions.h)

add_library(libkreuzstich ${SOURCES})
target_include_directories(libkreuzstich PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${ImageMagick_INCLUDE_DIRS})
