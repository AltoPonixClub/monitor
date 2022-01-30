cmake_minimum_required(VERSION 3.18)
project(qt)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/home/aoberai/programming/cpp/Qt/6.2.2/gcc_64/lib/cmake")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Charts
        OpenGL
        REQUIRED)

add_executable(qt main.cpp geometryengine.cpp geometryengine.h openglwidget.cpp openglwidget.h shaders.qrc textures.qrc)
target_link_libraries(qt
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Charts
        Qt::OpenGL
        )

# Resources:
set(shaders_resource_files
        "fshader.glsl"
        "vshader.glsl"
        )

qt6_add_resources(cube "shaders"
        FILES
        ${shaders_resource_files}
        )
set(textures_resource_files
        "cube.png"
)

qt6_add_resources(cube "textures"
        FILES
        ${textures_resource_files}
        )
