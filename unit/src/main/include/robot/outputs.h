#ifndef MONITOR_OUTPUTS_H
#define MONITOR_OUTPUTS_H

#include <string>
#include <opencv2/opencv.hpp>
#include <pangolin/gl/gl.h>
#include <config/constants.h>

// TODO: organize between subsystems
class Outputs {
public:
    Outputs() {};

    static Outputs *instance();

    // TODO: put in namespace?
    cv::Mat editedCapFrame, displayFrame;
    std::vector<Eigen::Matrix<float, 6, 1>> meshLines;
    std::vector<cv::Scalar> meshColor;
    std::vector<Eigen::Matrix<float, 4, 1>> frustumVerts;
    float logVal;

    //Uploader
    std::string jsonString = "";
private:
    static inline Outputs *pInstance = nullptr;
};

#endif //MONITOR_OUTPUTS_H