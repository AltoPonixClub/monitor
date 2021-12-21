//
// Created by aoberai on 12/20/21.
//

#include <string>
#include "utils.h"

template<typename T>
std::string Utils::vec2str(std::vector<T> arr) {
    std::string ot = std::string("[");
    for (auto v : arr) {
        ot += (std::to_string(v) + std::string(", "));
    }
    ot += std::string("]");
    return ot;
}

bool Utils::pairSortComparator(std::pair<int, std::vector<cv::Point2f>> a, std::pair<int, std::vector<cv::Point2f>> b) {
    return (a.first < b.first);
}

template std::string Utils::vec2str<int>(std::vector<int>);
template std::string Utils::vec2str<float>(std::vector<float>);
