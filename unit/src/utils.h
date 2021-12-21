//
// Created by aoberai on 12/20/21.
//

#ifndef MONITOR_UTILS_H
#define MONITOR_UTILS_H


#include <vector>
#include <opencv2/opencv.hpp>

class Utils {
public:
    template<typename T>
    static std::string vec2str(std::vector<T> array);
    static bool pairSortComparator(std::pair<int, std::vector<cv::Point2f>> a, std::pair<int, std::vector<cv::Point2f>> b);
};


#endif //MONITOR_UTILS_H
