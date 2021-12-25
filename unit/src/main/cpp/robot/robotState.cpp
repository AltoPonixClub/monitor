#include <robot/robotState.h>

cv::Mat capFrame = cv::Mat();

RobotState *RobotState::instance() {
    if (RobotState::pInstance == nullptr) {
        RobotState::pInstance = new RobotState();
    }
    return RobotState::pInstance;
}
