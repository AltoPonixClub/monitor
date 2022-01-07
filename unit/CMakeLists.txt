cmake_minimum_required(VERSION 3.21)
project(monitor)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(Pangolin 0.4 REQUIRED)
find_package(spdlog REQUIRED)
find_package(CURL REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS} ${EIGEN3_INCLUDE_DIR} ${Pangolin_INCLUDE_DIRS} src/main/include src/main/include/utils)
add_executable(${PROJECT_NAME} src/main/cpp/robot.cpp src/main/include/robot/state.h src/main/include/robot/outputs.h src/main/cpp/subsystems/vision.cpp src/main/include/subsystems/vision.h src/main/include/subsystems/subsystemBase.h src/main/cpp/robot/commands.cpp src/main/include/robot/commands.h src/main/cpp/subsystems/display.cpp src/main/include/subsystems/display.h src/main/cpp/subsystems/uploader.cpp src/main/include/subsystems/uploader.h src/main/include/config/constants.h src/main/cpp/utils/utils.cpp src/main/include/utils/utils.h src/main/cpp/robot/control.cpp src/main/include/robot/control.h src/main/include/subsystems/general.h src/main/cpp/subsystems/general.cpp src/main/cpp/robot/state.cpp src/main/cpp/robot/outputs.cpp src/main/include/subsystems/threadedBase.h src/main/cpp/subsystems/threadedBase.cpp src/main/include/subsystems/threadedManager.h src/main/cpp/subsystems/threadedManager.cpp src/main/cpp/restclient-cpp/restclient.cc src/main/cpp/restclient-cpp/connection.cc src/main/cpp/restclient-cpp/helpers.cc)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} ${EIGEN3_LIBS} ${Pangolin_LIBRARIES} ${CURL_LIBRARIES} spdlog::spdlog)