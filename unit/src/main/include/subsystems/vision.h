//
// Created by aoberai on 12/24/21.
//

#ifndef MONITOR_VISION_H
#define MONITOR_VISION_H

#include <iostream>
#include <subsystems/subsystemBase.h>
#include <opencv2/opencv.hpp>
#include <opencv2/aruco/dictionary.hpp>
#include <opencv2/aruco.hpp>
#include <config/constants.h>

// TODO: prevent data being read or uploaded from sensor in calculate func
class Vision : public SubsystemBase {
public:
    cv::VideoCapture cap;
    // TODO: this should prlly be moved out
    cv::Ptr<cv::aruco::Dictionary> arucoDictionary;
    cv::Ptr<cv::aruco::DetectorParameters> arucoParams;
    cv::FileStorage calibFile;
    cv::Mat cameraMatrix; // extrinsics
    cv::Mat distCoeffs; // intrinsics
    cv::Ptr<cv::aruco::Board> board;
    std::vector<cv::Point2f> transform_src;

    Vision();

    void read(State *state);

    void calculate(State *state, Commands *commands, Outputs *outputs);

    void write(Outputs *outputs);

    static Vision *instance();

    std::string name();

private:
    static inline Vision *pInstance = nullptr;
};

#endif //MONITOR_VISION_H
