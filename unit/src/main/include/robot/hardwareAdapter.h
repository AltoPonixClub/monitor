#ifndef MONITOR_HARDWAREADAPTER_H
#define MONITOR_HARDWAREADAPTER_H

#include <opencv2/opencv.hpp>
#include <robot/robotState.h>
#include <robot/outputs.h>

// TODO: this includes reader and writer; move to subsystem

class ItemHardware {
public:

    virtual void configure() = 0;

    virtual void read(RobotState *state) = 0;

    virtual void write(Outputs *outputs) = 0;

    static ItemHardware *instance();
};

class VisionHardware : public ItemHardware {
public:
    cv::VideoCapture cap;

    void configure();

    void read(RobotState *state);

    void write(Outputs *outputs);

    static VisionHardware *instance();

private:
    static inline VisionHardware *pInstance = nullptr;

    VisionHardware() {
    }
};

class DisplayHardware : public ItemHardware {
public:
    void configure();

    void read(RobotState *state);

    void write(Outputs *outputs);

    static DisplayHardware *instance();

private:
    static inline DisplayHardware *pInstance = nullptr;

    DisplayHardware() {
    }
};

#endif //MONITOR_HARDWAREADAPTER_H

