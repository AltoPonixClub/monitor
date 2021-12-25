#include "robot/hardwareAdapter.h"

/*
 * Singleton guide https://www.aristeia.com/Papers/DDJ_Jul_Aug_2004_revised.pdf
 */

VisionHardware* VisionHardware::instance() {
    if (VisionHardware::pInstance == nullptr) {
        VisionHardware::pInstance = new VisionHardware();
    }
    return VisionHardware::pInstance;
}

DisplayHardware* DisplayHardware::instance() {
    if (DisplayHardware::pInstance == nullptr) {
        DisplayHardware::pInstance = new DisplayHardware();
    }
    return DisplayHardware::pInstance;
}

void VisionHardware::configure() {
    if (!cap.isOpened()) {
        std::cout << "Vision Hardware Broken" << std::endl;
    }
}

void DisplayHardware::configure() {
    std::cout << "Display Hardware Initialized"
}

void VisionHardware::read() {
}

void DisplayHardware::read() {
}

void VisionHardware::write() {
}

void DisplayHardware::write() {
}
