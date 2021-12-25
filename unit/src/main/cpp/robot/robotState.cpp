#include <robot/robotState.h>

RobotState *RobotState::instance() {
    if (RobotState::pInstance == nullptr) {
        RobotState::pInstance = new RobotState();
    }
    return RobotState::pInstance;
}
