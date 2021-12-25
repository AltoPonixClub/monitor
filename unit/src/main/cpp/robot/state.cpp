#include <robot/state.h>
#include <config/constants.h>


void State::configure() {
    State::capFrame = cv::Mat();
    State::undistortedFrame = cv::Mat(constants::vision::imgSize.height, constants::vision::imgSize.width, CV_8UC3,
                                      cv::Scalar(100, 100, 100));
    State::cam_rvec, State::cam_tvec = cv::Vec3d(0, 0, 0);
}

State *State::instance() {
    if (State::pInstance == nullptr) {
        State::pInstance = new State();
    }
    return State::pInstance;
}
