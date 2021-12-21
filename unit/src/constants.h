//
// Created by luca on 12/21/21.
//

#ifndef MONITOR_CONSTANTS_H
#define MONITOR_CONSTANTS_H

namespace constants {
    int cameraId = 4;
    int imgWidth = 640;
    int imgHeight = 480;
    std::string calibPath = "/home/luca/code/monitor/unit/outputs.yml";
    std::vector<std::vector<std::vector<float>>> rawArucoPts = {{{0, 0, 0}, {0, 4.6, 0}, {4.6, 4.6, 0}, {4.6, 0, 0}},
                                                 {{16.1, 0, 0}, {16.1, 4.6, 0}, {20.7, 4.6, 0}, {20.7, 0, 0}},
                                                 {{0, 15.1, 0}, {0, 19.7, 0}, {4.6, 19.7, 0}, {4.6, 15.1, 0}},
                                                 {{16.1, 15.1, 0}, {16.1, 19.7, 0}, {20.7, 19.7, 0}, {20.7, 15.1, 0}}};
    std::vector<cv::Point2f> target = {cv::Point2f(0, 0), cv::Point2f(19.8, 0), cv::Point2f(19.8, 20.8), cv::Point2f(0, 20.8)};
    std::vector<int> arucoIds = {24, 42, 69, 48};
}

#endif //MONITOR_CONSTANTS_H
