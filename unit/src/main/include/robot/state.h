#ifndef MONITOR_STATE_H
#define MONITOR_STATE_H

#include <Eigen/Core>
#include <config/configs.h>
#include <opencv2/opencv.hpp>

class State {
  public:
    static State *instance();

    // Miscellaneous
    long initTimeS, timeS;
    int argc;
    char **argv;

    // Measurements
    float atmosphericTemp = 0;
    float reservoirTemp = 0;
    float lightIntensity = 0;
    float soilMoisture = 0;
    float electricalConductivity = 0;
    float pH = 0;
    float dissolvedOxygen = 0;
    float airFlow = 0;

    // Vision
    cv::Mat capFrame, undistortedFrame;
    cv::Vec3d camRvec, camTvec;
    cv::Mat camRotMat;
    std::vector<std::vector<float>> depthMap;
    std::vector<std::vector<cv::Point2f>> detectedArucoCorners,
        rejectedArucoCorners;
    std::vector<int> detectedArucoIds;
    std::vector<cv::Point2f> transform_dst;

    // Camera Position
    int indexCameraMove;

    // BlinkingLights
    int delayLED;
    bool ledIsOn;
    int nextToggleTime;

    // Uploader
    std::vector<float *> measurementPointers;
    std::vector<long> lastUploadTimes;
    std::string authToken;

  private:
    State(){};
    static inline State *pInstance = nullptr;
};

#endif // MONITOR_STATE_H
