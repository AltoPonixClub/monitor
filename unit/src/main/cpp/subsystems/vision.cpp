
#include <subsystems/vision.h>

Vision::VisionHardware *Vision::VisionHardware::instance() {
    if (VisionHardware::pInstance == nullptr) {
        VisionHardware::pInstance = new VisionHardware();
    }
    return VisionHardware::pInstance;
}

void Vision::VisionHardware::configure() {
    VisionHardware::cap = cv::VideoCapture(0);
    if (!cap.isOpened()) {
        std::cout << "Vision Hardware Broken" << std::endl;
    }
}

void Vision::VisionHardware::read(RobotState *state) {
    VisionHardware::cap >> state->capFrame;
}

void Vision::VisionHardware::write(Outputs *outputs) {
}

void Vision::calculate(RobotState *state, Commands *commands, Outputs *outputs) {
}

Vision *Vision::instance() {
    if (Vision::pInstance == nullptr) {
        Vision::pInstance = new Vision();
    }
    return Vision::pInstance;
}

std::string Vision::name() {
    return std::string("vision");
}

