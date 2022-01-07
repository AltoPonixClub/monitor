#ifndef MONITOR_STATE_H
#define MONITOR_STATE_H

#include <opencv2/opencv.hpp>
#include <Eigen/Core>
#include <config/constants.h>

class State {
public:
    State() {};

    static State *instance();

    // Miscellaneous
    float initTimeS, timeS;

    // Measurements
    float atmosphericTemp = 1;
    float reservoirTemp = 2;
    float lightIntensity = 3;
    float soilMoisture = 4;
    float electricalConductivity = 5;
    float pH = 6;
    float dissolvedOxygen = 7;
    float airFlow = 8;

    // Vision
    cv::Mat capFrame, undistortedFrame;
    cv::Vec3d camRvec, camTvec;
    cv::Mat camRotMat;
    std::vector<std::vector<float>> depthMap;
    std::vector<std::vector<cv::Point2f>> detectedArucoCorners, rejectedArucoCorners;
    std::vector<int> detectedArucoIds;
    std::vector<cv::Point2f> transform_dst;

    // Uploader
    std::vector<float*> measurementPointers;
    std::vector<long> lastUploadTimes;

private:
    static inline State *pInstance = nullptr;
};

#endif //MONITOR_STATE_H
