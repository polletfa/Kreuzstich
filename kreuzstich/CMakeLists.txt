cmake_minimum_required(VERSION 2.8.11)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

add_definitions(-DPROJECT_NAME="kreuzstich"
                -DMAJOR_VERSION=0
                -DMINOR_VERSION=1)

include_directories(/usr/include
                    /usr/local/include
                    ${LIBXML2_INCLUDE_DIR}
                    ${Boost_INCLUDE_DIRS})

set(SOURCES
    main.cpp
    error.cpp                           error.h
    version.cpp                         version.h
    dialogs/AboutDialog.cpp             dialogs/AboutDialog.h
    dialogs/ImportPictureDialog.cpp     dialogs/ImportPictureDialog.h
    dialogs/NewPictureDialog.cpp        dialogs/NewPictureDialog.h
                                        features/GenerateToolsInterface.h
    features/ImageToolsInterface.cpp    features/ImageToolsInterface.h
    features/SaveInterface.cpp          features/SaveInterface.h
    features/ZoomInterface.cpp          features/ZoomInterface.h
    tasks/ImportTask.cpp                tasks/ImportTask.h
    tasks/Task.cpp                      tasks/Task.h
    widgets/PictureLabel.cpp            widgets/PictureLabel.h
    windows/ChildWindow.cpp             windows/ChildWindow.h
    windows/Editor.cpp                  windows/Editor.h
    windows/MainWindow.cpp              windows/MainWindow.h)
set(UIS
    dialogs/AboutDialog.ui
    dialogs/ImportPictureDialog.ui
    dialogs/NewPictureDialog.ui
    windows/Editor.ui
    windows/MainWindow.ui)
set(RESOURCES
    resources/resources.qrc)

if(${USE_QT_VERSION} MATCHES 4)
    qt4_wrap_ui(UI_headers ${UIS})
    qt4_add_resources(RESOURCES_src ${RESOURCES})
    set(QT_TARGET Qt4::QtGui)
elseif(${USE_QT_VERSION} MATCHES 5)
    qt5_wrap_ui(UI_headers ${UIS})
    qt5_add_resources(RESOURCES_src ${RESOURCES})
    set(QT_TARGET Qt5::Widgets)
endif()

add_executable(kreuzstich ${SOURCES} ${UI_headers} ${RESOURCES_src})
target_link_libraries(kreuzstich libkreuzstich ${QT_TARGET}
    ${Boost_LIBRARIES} ${MAGICK_LDFLAGS} ${LIBXML2_LIBRARIES})
