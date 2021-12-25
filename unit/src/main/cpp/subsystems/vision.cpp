
#include "subsystems/vision.h"

void Vision::configure() {
    VisionHardware::instance()->configure();
}

void Vision::read(RobotState *state) {
    VisionHardware::instance()->read(state);
}

void Vision::calculate(RobotState *state, Commands *commands, Outputs *outputs) {
}

void Vision::write(Outputs *outputs) {
    VisionHardware::instance()->write(outputs);
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

