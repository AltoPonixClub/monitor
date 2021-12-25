#ifndef MONITOR_HARDWAREBASE_H
#define MONITOR_HARDWAREBASE_H

#include <opencv2/opencv.hpp>
#include <robot/robotState.h>
#include <robot/outputs.h>

// TODO: this includes reader and writer; move to subsystem

class HardwareBase {
public:

    virtual void configure() = 0;

    virtual void read(RobotState *state) = 0;

    virtual void write(Outputs *outputs) = 0;

    static HardwareBase *instance();
};

#endif //MONITOR_HARDWAREBASE_H

