//
// Created by aoberai on 12/20/21.
//

#include <string>
#include "utils.h"
#include <iostream>

template<typename T>
std::string Utils::vec2str(std::vector<T> arr) {
    std::string ot = std::string("[");
    for (auto v : arr) {
        ot += (std::to_string(v) + std::string(", "));
    }
    ot += std::string("]");
    return ot;
}

template std::string Utils::vec2str<int>(std::vector<int>);
template std::string Utils::vec2str<float>(std::vector<float>);
