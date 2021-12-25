#include <subsystems/display.h>
#include <config/constants.h>

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
    outputs->displayImg = state->undistortedFrame.empty() ? cv::Mat(constants::vision::imgSize.height, constants::vision::imgSize.width, CV_8UC3, cv::Scalar(100, 100, 100)) : state->undistortedFrame;
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


