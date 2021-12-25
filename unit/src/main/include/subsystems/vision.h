//
// Created by aoberai on 12/24/21.
//

#ifndef MONITOR_VISION_H
#define MONITOR_VISION_H

#include <iostream>
#include <subsystems/subsystemBase.h>

// TODO: prevent data being read or uploaded from sensor in calculate func
class Vision : public SubsystemBase {
public:
    cv::VideoCapture cap;

    void configure();

    void read(RobotState *state);

    void calculate(RobotState *state, Commands *commands, Outputs *outputs);

    void write(Outputs *outputs);

    static Vision *instance();

    std::string name();

private:
    static inline Vision *pInstance = nullptr;
};

#endif //MONITOR_VISION_H
