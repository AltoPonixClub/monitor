#ifndef MONITOR_HARDWAREADAPTER_H
#define MONITOR_HARDWAREADAPTER_H

#include <opencv2/opencv.hpp>
#include <robot/robotState.h>
#include <robot/outputs.h>

// TODO: this includes reader and writer


class HardwareAdapter {
public:
    static HardwareAdapter* instance();
    virtual void configure() = 0;
    virtual void read(RobotState state) = 0;
    virtual void write(Outputs outputs) = 0;
};

class VisionHardware : public HardwareAdapter {
public:
    cv::VideoCapture cap;
    void configure();
    void read(RobotState state);
    void write(Outputs outputs);
    static VisionHardware* instance();
private:
    static inline VisionHardware* pInstance = nullptr;
    VisionHardware() {
    }
};

class DisplayHardware : public HardwareAdapter {
public:
    void configure();
    void read(RobotState state);
    void write(Outputs outputs);
    static DisplayHardware* instance();
private:
    static inline DisplayHardware* pInstance = nullptr;
    DisplayHardware() {
    }
};

#endif //MONITOR_HARDWAREADAPTER_H

