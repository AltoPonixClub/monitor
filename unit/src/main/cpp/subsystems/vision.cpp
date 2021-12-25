
#include <subsystems/vision.h>

void Vision::configure() {
    cap = cv::VideoCapture(0);
    if (!cap.isOpened()) {
        std::cout << "Vision Hardware Broken" << std::endl;
        return;
    }
    std::cout << "Display Hardware Initialized";
}

void Vision::read(RobotState *state) {
    cap >> state->capFrame;
}

void Vision::write(Outputs *outputs) {
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

