//
// Created by luca on 12/21/21.
//

#ifndef MONITOR_CONSTANTS_H
#define MONITOR_CONSTANTS_H


namespace constants {
    const int kCameraId = 0;
    const cv::Size kDispSize = cv::Size(int(640 * 2), int(480 * 2));
    const cv::Size kImgSize = cv::Size(int(640), int(480));
    const cv::Size kImgDispSize = cv::Size(int(640), int(2 * 480));
    const cv::Size kPlatformDim = cv::Size(20.7, 19.7);
//    const int ui_width = 20 * pangolin::default_font().MaxWidth();
    const int kFps = 60;
    const std::string kCalibPath = "/home/aoberai/programming/altoponix/monitor/unit/outputs.yml";
    const cv::Scalar kAqua(255, 255, 0);
    const int kArucoCircRadius = 4;
    const std::vector <std::vector<cv::Point3f>> kBoardArucoPts = {{cv::Point3f(0, 0, 0),       cv::Point3f(0, 4.6,
                                                                                                           0), cv::Point3f(
            4.6, 4.6, 0),                                                                 cv::Point3f(4.6, 0, 0)},
                                                                  {cv::Point3f(16.1, 0, 0),    cv::Point3f(16.1, 4.6,
                                                                                                           0), cv::Point3f(
                                                                          20.7, 4.6, 0),  cv::Point3f(20.7, 0, 0)},
                                                                  {cv::Point3f(0, 15.1, 0),    cv::Point3f(0, 19.7,
                                                                                                           0), cv::Point3f(
                                                                          4.6, 19.7, 0),  cv::Point3f(4.6, 15.1, 0)},
                                                                  {cv::Point3f(16.1, 15.1, 0), cv::Point3f(16.1, 19.7,
                                                                                                           0), cv::Point3f(
                                                                          20.7, 19.7, 0), cv::Point3f(20.7, 15.1, 0)}};
    const std::vector<int> kArucoIds = {24, 42, 69, 48};
}

#endif //MONITOR_CONSTANTS_H
