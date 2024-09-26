#ifndef MONITOR_VISION_H
#define MONITOR_VISION_H

#include "config/configs.h"
#include "subsystemBase.h"
#include <iostream>
#include <opencv2/aruco.hpp>
#include <opencv2/aruco/dictionary.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/ximgproc/disparity_filter.hpp>

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
    cv::VideoCapture *leftCap;
    cv::VideoCapture *rightCap;
    cv::Ptr<cv::StereoSGBM> leftMatcher; // TODO: var naming
    cv::Ptr<cv::StereoMatcher> rightMatcher;
    cv::Ptr<cv::ximgproc::DisparityWLSFilter> wlsFilter;
    // TODO: constants remove
    std::vector<cv::Point2f> transform_src;

    static inline Vision *pInstance = nullptr;
};

#endif // MONITOR_VISION_H
