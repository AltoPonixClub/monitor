#ifndef MONITOR_STATE_H
#define MONITOR_STATE_H

#include <Eigen/Core>
#include <config/configs.h>
#include <opencv2/opencv.hpp>

class State {
  public:
    State(){};

    static State *instance();

    // Miscellaneous
    float initTimeS, timeS;

    // Vision
    cv::Mat capFrame, undistortedFrame;
    cv::Vec3d camRvec, camTvec;
    cv::Mat camRotMat;
    std::vector<std::vector<float>> depthMap;
    std::vector<std::vector<cv::Point2f>> detectedArucoCorners,
        rejectedArucoCorners;
    std::vector<int> detectedArucoIds;
    std::vector<cv::Point2f> transform_dst;

  private:
    static inline State *pInstance = nullptr;
};

#endif // MONITOR_STATE_H
