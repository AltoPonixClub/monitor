#include <opencv2/imgcodecs.hpp>
#include <spdlog/spdlog.h>
#include "utils/dummyVideoCapture.h"
#include "subsystems/vision.h"



DummyVideoCapture::DummyVideoCapture(std::string filename) {
    cv::resize(cv::imread(filename), img, Configs::Vision::kImgSize);
}

DummyVideoCapture::DummyVideoCapture() {
    cv::resize(cv::imread(Configs::Vision::kBlankPath), img, Configs::Vision::kImgSize);
}

DummyVideoCapture& DummyVideoCapture::operator >> (cv::Mat& image) {
    image = img.clone();
    return *this;
}


