#ifndef MONITOR_DISPLAY_H
#define MONITOR_DISPLAY_H

#include <iostream>
#include <subsystems/subsystemBase.h>
#include <robot/hardwareAdapter.h>

class Display : public SubsystemBase {
public:
    void configure();

    void read(RobotState *state);

    void calculate(RobotState *state, Commands *commands, Outputs *outputs);

    void write(Outputs *outputs);

    static Display *instance();

    std::string name();

private:
    static inline Display *pInstance = nullptr;
};

#endif //MONITOR_DISPLAY_H
