#include <iostream>
#include <robot/hardwareAdapter.h>
#include <robot/robotState.h>

using namespace std;

int main() {
    RobotState* state = RobotState::instance();
    Outputs* outputs = Outputs::instance();

    // Init
    HardwareAdapter::configureHardware();

    // Periodic
    while (true) {
        HardwareAdapter::readHardware(state);
        outputs->displayImg = state->capFrame.clone(); // this in subsystem logic
        HardwareAdapter::writeHardware(outputs);
    }
}
