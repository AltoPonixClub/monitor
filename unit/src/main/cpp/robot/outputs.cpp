#include <robot/outputs.h>
#include <config/constants.h>
#include <utils/utils.h>


Outputs::Outputs() {
    this->displayFrame = cv::Mat(constants::vision::imgSize.height, constants::vision::imgSize.width, CV_8UC3,
                                 cv::Scalar(100, 100, 100));
    this->frustumVerts = Utils::getFrustumVertices(-0.5, -0.5, 1, 1, 1, 1, 1);
    this->logVal = 0;
}

Outputs *Outputs::instance() {
    if (Outputs::pInstance == nullptr) {
        Outputs::pInstance = new Outputs();
    }
    return Outputs::pInstance;
}

