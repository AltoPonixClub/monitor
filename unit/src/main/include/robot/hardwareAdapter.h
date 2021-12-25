//
// Created by aoberai on 12/24/21.
//

#ifndef MONITOR_HARDWAREADAPTER_H
#define MONITOR_HARDWAREADAPTER_H

#include <opencv2/opencv.hpp>

// TODO: this includes reader and writer


class HardwareAdapter {
public:
    static HardwareAdapter* instance();
    virtual void configure() = 0;
    virtual void read() = 0;
    virtual void write() = 0;
};

class VisionHardware : public HardwareAdapter {
public:
    cv::VideoCapture cap;
    void configure();
    void read();
    void write();
    static VisionHardware* instance();
private:
    static inline VisionHardware* pInstance = nullptr;
    VisionHardware() {
    }
};

class DisplayHardware : public HardwareAdapter {
public:
    void configure();
    void read();
    void write();
    static DisplayHardware* instance();
private:
    static inline DisplayHardware* pInstance = nullptr;
    DisplayHardware() {
    }
};

#endif //MONITOR_HARDWAREADAPTER_H

