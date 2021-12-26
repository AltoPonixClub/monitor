#ifndef MONITOR_OUTPUTS_H
#define MONITOR_OUTPUTS_H

#include <opencv2/opencv.hpp>
#include <pangolin/gl/gl.h>
#include <config/constants.h>

// TODO: organize between subsystems
class Outputs {
public:
    Outputs();

    static Outputs *instance();

    // TODO: put in namespace?
    cv::Mat displayFrame;
    std::vector<Eigen::Matrix<float, 4, 1>> frustumVerts;
    float logVal;

private:
    static inline Outputs *pInstance = nullptr;
};

#endif //MONITOR_OUTPUTS_H
