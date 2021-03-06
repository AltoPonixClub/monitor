cmake_minimum_required(VERSION 3.16)
project(monitor)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(Pangolin 0.4 REQUIRED)
find_package(spdlog REQUIRED)
find_package(CURL REQUIRED)
find_package(Qt6 COMPONENTS Core OpenGL SerialPort REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS} ${EIGEN3_INCLUDE_DIR} ${Pangolin_INCLUDE_DIRS} ${Qt6Core_INCLUDE_DIRS} ${Qt6OpenGL_INCLUDE_DIRS} ${Qt6SerialPort_INCLUDE_DIRS} src)
add_executable(${PROJECT_NAME} src/robot/robot.cpp src/robot/state.h src/robot/outputs.h src/subsystems/vision.cpp src/subsystems/vision.h src/subsystems/subsystemBase.h src/robot/commands.cpp src/robot/commands.h src/subsystems/display.cpp src/subsystems/display.h src/subsystems/uploader.cpp src/subsystems/uploader.h src/config/secrets.h src/config/configs.h src/config/configs.cpp src/utils/utils.cpp src/utils/utils.h src/robot/control.cpp src/robot/control.h src/subsystems/miscellaneous.h src/subsystems/miscellaneous.cpp src/robot/state.cpp src/robot/outputs.cpp src/utils/restclient.cpp src/utils/connection.cpp src/utils/helpers.cpp src/utils/daq.cpp src/utils/daq.h src/utils/json.h src/utils/json.cpp src/subsystems/blinkingLights.cpp src/subsystems/blinkingLights.h src/subsystems/threaderer.h src/subsystems/threaderer.cpp src/utils/pidController.h src/utils/pidController.cpp src/utils/dummyVideoCapture.cpp src/utils/dummyVideoCapture.h src/routines/routinerer.cpp src/routines/routinerer.h src/routines/routineBase.h)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} ${EIGEN3_LIBS} ${Pangolin_LIBRARIES} ${CURL_LIBRARIES} Qt::Core Qt::OpenGL Qt::SerialPort spdlog::spdlog)
