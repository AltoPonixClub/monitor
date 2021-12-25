cmake_minimum_required(VERSION 3.21)
project(monitor)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(Pangolin 0.4 REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} ${EIGEN3_INCLUDE_DIR} ${Pangolin_INCLUDE_DIRS} src/main/include)
add_executable( ${PROJECT_NAME} src/main/cpp/robot.cpp src/main/cpp/robot/hardwareAdapter.cpp src/main/include/robot/hardwareAdapter.h src/main/cpp/robot/robotState.cpp src/main/include/robot/robotState.h src/main/cpp/robot/outputs.cpp src/main/include/robot/outputs.h)
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} ${EIGEN3_LIBS} ${Pangolin_LIBRARIES})
