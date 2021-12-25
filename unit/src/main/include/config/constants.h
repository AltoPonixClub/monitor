#ifndef MONITOR_CONSTANTS_H
#define MONITOR_CONSTANTS_H

#include <opencv2/opencv.hpp>

// TODO: Need a source file?
// TODO: doesnt follow clang style guide

namespace constants {
    namespace vision {
        const int cameraId = 0;
        const cv::Size dispSize = cv::Size(int(640 * 2), int(480 * 2));
        const cv::Size imgSize = cv::Size(int(640), int(480));
        const cv::Size imgDispSize = cv::Size(int(640), int(2 * 480));
        const cv::Size platformDim = cv::Size(20.7, 19.7);
        //    const int ui_width = 20 * pangolin::default_font().MaxWidth();
        const int fps = 60;
        const std::string calibPath = std::string("/home/aoberai/programming/altoponix/monitor/unit/outputs.yml");
        const cv::Scalar aqua(255, 255, 0);
        const int arucoCircRadius = 4;
        const std::vector<std::vector<cv::Point3f>> boardArucoPts = {{cv::Point3f(0, 0, 0),       cv::Point3f(0, 4.6,
                                                                                                              0), cv::Point3f(
                4.6, 4.6, 0),                                                                cv::Point3f(4.6, 0, 0)},
                                                                     {cv::Point3f(16.1, 0, 0),    cv::Point3f(16.1, 4.6,
                                                                                                              0), cv::Point3f(
                                                                             20.7, 4.6, 0),  cv::Point3f(20.7, 0, 0)},
                                                                     {cv::Point3f(0, 15.1, 0),    cv::Point3f(0, 19.7,
                                                                                                              0), cv::Point3f(
                                                                             4.6, 19.7, 0),  cv::Point3f(4.6, 15.1, 0)},
                                                                     {cv::Point3f(16.1, 15.1, 0), cv::Point3f(16.1,
                                                                                                              19.7,
                                                                                                              0), cv::Point3f(
                                                                             20.7, 19.7, 0), cv::Point3f(20.7, 15.1,
                                                                                                         0)}};
        const std::vector<int> arucoIds = {24, 42, 69, 48};
    };
};

#endif //MONITOR_CONSTANTS_H
