//
// Created by aoberai on 12/24/21.
//

#ifndef MONITOR_VISION_H
#define MONITOR_VISION_H

#include <iostream>
#include <subsystems/subsystemBase.h>
#include <robot/hardwareAdapter.h>

class Vision : public SubsystemBase {
public:
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
