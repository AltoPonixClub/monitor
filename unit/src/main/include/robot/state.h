#ifndef MONITOR_STATE_H
#define MONITOR_STATE_H

#include <opencv2/opencv.hpp>

class State {
public:
    static State *instance();

    void configure();

    // Physical
    float time; // TODO: physical state subsystem

    // Vision
    cv::Mat capFrame, undistortedFrame;
    cv::Vec3d cam_rvec, cam_tvec;
    std::vector<std::vector<cv::Point2f>> detectedArucoCorners, rejectedArucoCorners;
    std::vector<int> detectedArucoIds;
    std::vector<cv::Point2f> transform_dst;
private:
    static inline State *pInstance = nullptr;
};

#endif //MONITOR_STATE_H
