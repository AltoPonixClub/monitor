#include <robot/state.h>
#include <config/constants.h>


// TODO: should this stuff be initialized in subsystem or here? (same for commands etc)
State::State() {
    this->time = 0;
    this->capFrame = cv::Mat();
    this->undistortedFrame = cv::Mat(constants::vision::kImgSize.height, constants::vision::kImgSize.width, CV_8UC3,
                                     cv::Scalar(100, 100, 100));
    this->cam_rvec, this->cam_tvec = cv::Vec3d(0, 0, 0);
}

State *State::instance() {
    if (State::pInstance == nullptr) {
        State::pInstance = new State();
    }
    return State::pInstance;
}
