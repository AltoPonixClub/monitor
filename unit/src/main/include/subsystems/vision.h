//
// Created by aoberai on 12/24/21.
//

#ifndef MONITOR_VISION_H
#define MONITOR_VISION_H

#include <iostream>
#include <subsystems/subsystemBase.h>
#include <subsystems/hardwareBase.h>

class Vision : public SubsystemBase {
public:
    class VisionHardware : public HardwareBase {
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
