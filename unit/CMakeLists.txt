cmake_minimum_required(VERSION 3.21)
project(monitor)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(Pangolin 0.4 REQUIRED)
find_package(spdlog REQUIRED)
find_package(Qt6 COMPONENTS SerialPort REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS} ${EIGEN3_INCLUDE_DIR} ${Pangolin_INCLUDE_DIRS} ${Qt6SerialPort_INCLUDE_DIRS} src/main/include)
add_executable(${PROJECT_NAME} src/main/cpp/robot.cpp src/main/include/robot/state.h src/main/include/robot/outputs.h src/main/cpp/subsystems/vision.cpp src/main/include/subsystems/vision.h src/main/include/subsystems/subsystemBase.h src/main/cpp/robot/commands.cpp src/main/include/robot/commands.h src/main/cpp/subsystems/display.cpp src/main/include/subsystems/display.h src/main/include/config/constants.h src/main/cpp/utils/utils.cpp src/main/include/utils/utils.h src/main/cpp/robot/control.cpp src/main/include/robot/control.h src/main/include/subsystems/general.h src/main/cpp/subsystems/general.cpp src/main/cpp/robot/state.cpp src/main/cpp/robot/outputs.cpp)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} ${EIGEN3_LIBS} ${Pangolin_LIBRARIES} Qt::SerialPort spdlog::spdlog)
