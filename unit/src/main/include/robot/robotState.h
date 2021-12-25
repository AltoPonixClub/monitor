#ifndef MONITOR_ROBOTSTATE_H
#define MONITOR_ROBOTSTATE_H

#include <opencv2/opencv.hpp>

class RobotState {
public:
    static RobotState *instance();
    cv::Mat capFrame;
private:
    static inline RobotState *pInstance = nullptr;
};

#endif //MONITOR_ROBOTSTATE_H
