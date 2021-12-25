#ifndef MONITOR_OUTPUTS_H
#define MONITOR_OUTPUTS_H

#include <opencv2/opencv.hpp>
#include <pangolin/gl/gl.h>
#include <config/constants.h>

// TODO: organize between subsystems
class Outputs {
public:
    static Outputs *instance();

    void configure();

    cv::Mat displayImg;
    pangolin::GlTexture imageTexture;
private:
    static inline Outputs *pInstance = nullptr;
};

#endif //MONITOR_OUTPUTS_H
