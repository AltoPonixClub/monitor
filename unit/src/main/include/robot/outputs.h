#ifndef MONITOR_OUTPUTS_H
#define MONITOR_OUTPUTS_H

#include <opencv2/opencv.hpp>

class Outputs {
public:
    static Outputs *instance();

    cv::Mat displayImg;
private:
    static inline Outputs *pInstance = nullptr;
};

#endif //MONITOR_OUTPUTS_H
