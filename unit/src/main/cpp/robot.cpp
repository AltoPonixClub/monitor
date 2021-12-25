#include <iostream>
#include <robot/hardwareAdapter.h>
#include <robot/robotState.h>

using namespace std;

int main() {
    RobotState* state = RobotState::instance();
    // Init
    HardwareAdapter::configureHardware();

    // Periodic
    while (true) {
        HardwareAdapter::readHardware(state);
    }
}
