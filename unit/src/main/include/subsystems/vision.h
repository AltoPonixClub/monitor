#ifndef MONITOR_VISION_H
#define MONITOR_VISION_H

#include <config/configs.h>
#include <iostream>
#include <opencv2/aruco.hpp>
#include <opencv2/aruco/dictionary.hpp>
#include <opencv2/opencv.hpp>
#include <subsystems/subsystemBase.h>

// TODO: prevent data being read or uploaded from sensor in calculate func
class Vision : public SubsystemBase {
  public:
    Vision(State *state, Commands *commands, Outputs *outputs);

    void read(State *state, Commands *commands);

    void calculate(State *state, Commands *commands, Outputs *outputs);

    void write(Outputs *outputs);

    bool threaded();

    static Vision *instance(State *state, Commands *commands, Outputs *outputs);

    std::string name();

  private:
    cv::VideoCapture leftCap, rightCap;

    // TODO: constants remove
    cv::FileStorage calibFile;
    cv::Mat cameraMatrix; // extrinsics
    cv::Mat distCoeffs;   // intrinsics
    std::vector<cv::Point2f> transform_src;

    static inline Vision *pInstance = nullptr;
};

#endif // MONITOR_VISION_H
