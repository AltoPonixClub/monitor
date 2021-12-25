
#include <subsystems/display.h>

void Display::configure() {
    std::cout << "Display Hardware Initialized" << std::endl;
}

void Display::read(RobotState *state) {
}

void Display::write(Outputs *outputs) {
    cv::imshow("Window", outputs->displayImg);
    cv::waitKey(1);
}

void Display::calculate(RobotState *state, Commands *commands, Outputs *outputs) {
    if (commands->visionWantedState == commands->STREAMING) {
        outputs->displayImg = state->capFrame.clone();
    }
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


