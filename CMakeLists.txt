# TODO:
# - writescript fehler handlung?
# - generatescript / dialog to select unit and fabric count
# - oder size in mm/inch schon beim erstellen eines projektes + dialog um parameter nachträglich zu ändern?
# - tools: pen / fill / replace
# - imagemagick fehlerhandlung müsste noch überprüft werden (warnings? weitere versuche mit nicht-bild-dateien)
# - doxy & mehr kommentaren (und Header)
# - l10n (auch libKreuzstich)
#   --> im prinzip nichts außer writescript
#########################################

cmake_minimum_required(VERSION 2.8.11)
project(Kreuzstich)

#set(USE_QT_VERSION 4)
set(USE_QT_VERSION 5)

# Build shared libraries
set(BUILD_SHARED_LIBS ON)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Set C++ standard to C++11
add_definitions(-std=c++11)

# Git commit hash & build time (note: computed when cmake is run, not make, so only correct with a clean build)
execute_process(COMMAND git log --pretty=format:%h -n1 HEAD
                OUTPUT_VARIABLE GIT_COMMIT)
execute_process(COMMAND date "+%s"
                COMMAND tr -d "\n"
                OUTPUT_VARIABLE BUILD_TIME)
               
add_definitions(-DGIT_COMMIT="${GIT_COMMIT}"
                -DBUILD_TIME="${BUILD_TIME}" )

# Copyright
add_definitions(-DCOPYRIGHT="2013-2020, Fabien Pollet \(polletfa@posteo.de\)")

# System information
add_definitions(-DSYSTEM="${CMAKE_SYSTEM}"
                -DPROCESSOR="${CMAKE_SYSTEM_PROCESSOR}")

# Packages
find_package(ImageMagick 6 REQUIRED COMPONENTS Magick++ MagickCore)
execute_process(COMMAND pkg-config Magick++ --cflags
                OUTPUT_VARIABLE MAGICK_CPPFLAGS
                OUTPUT_STRIP_TRAILING_WHITESPACE)
add_definitions(${MAGICK_CPPFLAGS})
execute_process(COMMAND pkg-config Magick++ --libs
                OUTPUT_VARIABLE MAGICK_LDFLAGS
                OUTPUT_STRIP_TRAILING_WHITESPACE)
find_package(Boost REQUIRED COMPONENTS system filesystem program_options regex)
if(${USE_QT_VERSION} MATCHES 4)
    find_package(Qt4 REQUIRED QtGui)
elseif(${USE_QT_VERSION} MATCHES 5)
    find_package(Qt5Widgets)
else()
    message(FATAL_ERROR "USE_QT_VERSION must be set to 4 or 5.")
endif()
add_definitions(-DUSE_QT_VERSION=${USE_QT_VERSION})
find_package(LibXml2)

# Subdirectories
add_subdirectory(libkreuzstich)
add_subdirectory(kreuzstich)
