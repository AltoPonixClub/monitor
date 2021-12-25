#ifndef MONITOR_ROBOTSTATE_H
#define MONITOR_ROBOTSTATE_H

#include <opencv2/opencv.hpp>

class RobotState {
public:
    static RobotState *instance();

    cv::Mat capFrame, undistortedFrame;
    cv::Vec3d cam_rvec, cam_tvec;
    std::vector<std::vector<cv::Point2f>> detectedArucoCorners, rejectedArucoCorners;
    std::vector<int> detectedArucoIds;
    std::vector<cv::Point2f> transform_dst;
private:
    static inline RobotState *pInstance = nullptr;
};

#endif //MONITOR_ROBOTSTATE_H
