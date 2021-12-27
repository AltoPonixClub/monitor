#ifndef MONITOR_CONSTANTS_H
#define MONITOR_CONSTANTS_H

#include <opencv2/opencv.hpp>
#include <opencv2/aruco/dictionary.hpp>
#include <opencv2/aruco.hpp>

// TODO: Need a source file?
// TODO: doesnt follow clang style guide

namespace constants {
    namespace physical {
        const cv::Size kPlatformDim = cv::Size(20.7, 19.7);
        const float kPeriod = 0.02; // TODO: fix
    }
    namespace vision {
        const int kCameraId = 0;
        const cv::Size kImgSize = cv::Size(int(640), int(480));
        const int kFps = 60;
        const std::string kCalibPath = std::string("/home/aoberai/programming/altoponix/monitor/unit/outputs.yml");
        const std::vector<std::vector<cv::Point3f>> kBoardArucoPts = {{cv::Point3f(0, 0, 0), cv::Point3f(0, 4.6,0), cv::Point3f(4.6, 4.6, 0), cv::Point3f(4.6, 0, 0)}, {cv::Point3f(16.1, 0, 0),    cv::Point3f(16.1,4.6,0), cv::Point3f(20.7, 4.6, 0),  cv::Point3f(20.7, 0, 0)},{cv::Point3f(0, 15.1, 0), cv::Point3f(0, 19.7,0), cv::Point3f(4.6, 19.7, 0),  cv::Point3f(4.6, 15.1,0)},{cv::Point3f(16.1, 15.1, 0), cv::Point3f(16.1,19.7,0), cv::Point3f(20.7, 19.7, 0), cv::Point3f(20.7, 15.1,0)}};
        const cv::Ptr<cv::aruco::Dictionary> kArucoDictionary = cv::aruco::Dictionary::get(cv::aruco::DICT_5X5_100);
        const cv::Ptr<cv::aruco::DetectorParameters> kArucoParams = cv::aruco::DetectorParameters::create();
        const std::vector<int> kArucoIds = {24, 42, 69, 48};
        const cv::Ptr<cv::aruco::Board> kBoard = cv::aruco::Board::create(kBoardArucoPts, kArucoDictionary, kArucoIds);
    };
    namespace display {
        const cv::Size kDispSize = cv::Size(int(640 * 2), int(480 * 2));
        const cv::Size kImgDispSize = cv::Size(int(640), int(2 * 480));
        const float kMeshDensity = 100.0; // must be float
        const int kArucoCircRadius = 7;
        const cv::Scalar kAqua(255, 255, 0); // BGR
        const cv::Scalar kGrey(100, 100, 100); // BGR
        const cv::Scalar kBlack(0, 0, 0); // BGR
    }
};

#endif //MONITOR_CONSTANTS_H
