#include <robot/robotState.h>
#include <config/constants.h>

cv::Mat capFrame = cv::Mat();
cv::Mat undistortedFrame = cv::Mat(constants::vision::imgSize.height, constants::vision::imgSize.width, CV_8UC3, cv::Scalar(100, 100, 100));
cv::Vec3d cam_rvec, cam_tvec = cv::Vec3d(0, 0, 0);

RobotState *RobotState::instance() {
    if (RobotState::pInstance == nullptr) {
        RobotState::pInstance = new RobotState();
    }
    return RobotState::pInstance;
}
