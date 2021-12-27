#include <robot/state.h>
#include <config/constants.h>
#include "utils/utils.h"


// TODO: should this stuff be initialized in subsystem or here? (same for commands etc) (prlly subsystem?)
State::State() {
    this->time = 0;
    this->capFrame = cv::Mat();
    this->undistortedFrame = cv::Mat(constants::vision::kImgSize.height, constants::vision::kImgSize.width, CV_8UC3,
                                     cv::Scalar(100, 100, 100));
    this->camRvec, this->camTvec = cv::Vec3d(0, 0, 0);
    this->depthMap = std::vector<std::vector<float>>(constants::vision::kImgSize.height, std::vector<float> (constants::vision::kImgSize.width, 0));
}

State *State::instance() {
    if (State::pInstance == nullptr) {
        State::pInstance = new State();
    }
    return State::pInstance;
}
