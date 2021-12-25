#include "robot/hardwareAdapter.h"

/*
 * Singleton guide https://www.aristeia.com/Papers/DDJ_Jul_Aug_2004_revised.pdf
 */

void HardwareAdapter::configureHardware() {
    HardwareAdapter::VisionHardware::instance()->configure();
    HardwareAdapter::DisplayHardware::instance()->configure();
}

void HardwareAdapter::readHardware(RobotState* state) {
    HardwareAdapter::VisionHardware::instance()->read(state);
    HardwareAdapter::DisplayHardware::instance()->read(state);
}

void HardwareAdapter::writeHardware(Outputs outputs) {
    HardwareAdapter::VisionHardware::instance()->write(outputs);
    HardwareAdapter::DisplayHardware::instance()->write(outputs);
}


HardwareAdapter::VisionHardware* HardwareAdapter::VisionHardware::instance() {
    if (VisionHardware::pInstance == nullptr) {
        VisionHardware::pInstance = new VisionHardware();
    }
    return VisionHardware::pInstance;
}

HardwareAdapter::DisplayHardware* HardwareAdapter::DisplayHardware::instance() {
    if (DisplayHardware::pInstance == nullptr) {
        DisplayHardware::pInstance = new DisplayHardware();
    }
    return DisplayHardware::pInstance;
}

void HardwareAdapter::VisionHardware::configure() {
    if (!cap.isOpened()) {
        std::cout << "Vision Hardware Broken" << std::endl;
    }
}

void HardwareAdapter::DisplayHardware::configure() {
    std::cout << "Display Hardware Initialized" << std::endl;
}

void HardwareAdapter::VisionHardware::read(RobotState* state) {
    HardwareAdapter::VisionHardware::cap >> state->capFrame;
}

void HardwareAdapter::DisplayHardware::read(RobotState* state) {
}

void HardwareAdapter::VisionHardware::write(Outputs outputs) {
}

void HardwareAdapter::DisplayHardware::write(Outputs outputs) {
}
