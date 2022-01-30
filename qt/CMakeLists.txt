cmake_minimum_required(VERSION 3.18)
project(qt)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Charts
        OpenGL
        REQUIRED)
include_directories(src/include)
set(RESOURCE_FILES assets/shaders/shaders.qrc assets/textures/textures.qrc)
#add_executable(qt src/cpp/main.cpp src/cpp/util/geometryengine.cpp src/include/util/geometryengine.h src/cpp/widgets/openglwidget.cpp src/include/widgets/openglwidget.h assets/resources/shaders.qrc assets/resources/textures.qrc)
add_executable(qt
        src/cpp/main.cpp
        src/include/views/viewBase.h src/cpp/views/viewBase.cpp
        src/include/views/chartView.h src/cpp/views/chartView.cpp
        src/include/views/openglView.h src/cpp/views/openglView.cpp
        src/include/util/geometryengine.h src/cpp/util/geometryengine.cpp
        ${RESOURCE_FILES}
        )
target_link_libraries(qt
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Charts
        Qt::OpenGL
        )

# Resources:
#set(shaders_resource_files
#        "assets/shaders/noop.frag"
#        "assets/shaders/noop.vert"
#        )
#
#qt6_add_resources(cube "shaders"
#        FILES
#        ${shaders_resource_files}
#        )
#set(textures_resource_files
#        "cube.png"
#)
#
#qt6_add_resources(cube "textures"
#        FILES
#        ${textures_resource_files}
#        )
