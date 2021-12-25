#include <robot/outputs.h>
#include <config/constants.h>


void Outputs::configure() {
    Outputs::displayImg = cv::Mat(constants::vision::imgSize.height, constants::vision::imgSize.width, CV_8UC3,
                                  cv::Scalar(100, 100, 100));
    Outputs::imageTexture = pangolin::GlTexture(constants::display::imgDispSize.width,
                                                constants::display::imgDispSize.height, GL_RGB, false, 0, GL_RGB,
                                                GL_UNSIGNED_BYTE);
}

Outputs *Outputs::instance() {
    if (Outputs::pInstance == nullptr) {
        Outputs::pInstance = new Outputs();
    }
    return Outputs::pInstance;
}

