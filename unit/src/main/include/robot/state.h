#ifndef MONITOR_STATE_H
#define MONITOR_STATE_H

#include <opencv2/opencv.hpp>
#include <config/constants.h>

class State {
public:
    State() {};

    static State *instance();

    // General
    float initTimeS, timeS;
    float monitorMeasurements[constants::general::kNumMeasurements] = { 1, 2, 3, 4, 5, 6, 7, 8 };

    // Vision
    cv::Mat capFrame, undistortedFrame;
    cv::Vec3d camRvec, camTvec;
    std::vector<std::vector<float>> depthMap;
    std::vector<std::vector<cv::Point2f>> detectedArucoCorners, rejectedArucoCorners;
    std::vector<int> detectedArucoIds;
    std::vector<cv::Point2f> transform_dst;

    //Uploading
    long lastTimeS;
    bool doUpload = false;

private:
    static inline State *pInstance = nullptr;
};

#endif //MONITOR_STATE_H
