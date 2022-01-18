//
// Created by aoberai on 1/18/22.
//

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <spdlog/spdlog.h>
#include "utils/dummyVideoCapture.h"
#include "subsystems/vision.h"

DummyVideoCapture::DummyVideoCapture() {
    cv::resize(cv::imread(Configs::Vision::kBlankPath), img, Configs::Vision::kImgSize);
}


DummyVideoCapture::DummyVideoCapture(std::string filename) {
    cv::resize(cv::imread(filename), img, Configs::Vision::kImgSize);
//    if (img.empty()) {
//        spdlog::error("Dummy Video Cap Not Working!");
//    }

//    cv::imshow("win", img);
//    cv::waitKey(0);
}
// TODO: why this not being called
DummyVideoCapture& DummyVideoCapture::operator >> (CV_OUT cv::Mat& image) {
    std::cout << "asldkfjhasdkfhj";
    image = img.clone();
    return *this;
}


