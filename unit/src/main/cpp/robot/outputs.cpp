#include <robot/outputs.h>
#include <config/constants.h>

// TODO: fix this cuz this aint working also remove from display.cpp many objects
cv::Mat displayImg = cv::Mat(constants::vision::imgSize.height, constants::vision::imgSize.width, CV_8UC3,
                             cv::Scalar(100, 100, 100));
pangolin::GlTexture imageTexture = pangolin::GlTexture(constants::display::imgDispSize.width,
                                                       constants::display::imgDispSize.height, GL_RGB, false, 0, GL_RGB,
                                                       GL_UNSIGNED_BYTE);

Outputs *Outputs::instance() {
    if (Outputs::pInstance == nullptr) {
        Outputs::pInstance = new Outputs();
    }
    return Outputs::pInstance;
}
