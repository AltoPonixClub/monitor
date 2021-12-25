
#include "subsystems/display.h"

void Display::configure() {
    DisplayHardware::instance()->configure();
}

void Display::read(RobotState *state) {
    VisionHardware::instance()->read(state);
}

void Display::calculate(RobotState *state, Commands *commands, Outputs *outputs) {
    if (commands->visionWantedState == commands->STREAMING) {
        outputs->displayImg = state->capFrame.clone();
    }
}

void Display::write(Outputs *outputs) {
    DisplayHardware::instance()->write(outputs);
}

Display *Display::instance() {
    if (Display::pInstance == nullptr) {
        Display::pInstance = new Display();
    }
    return Display::pInstance;
}

std::string Display::name() {
    return std::string("display");
}


