#ifndef MONITOR_DISPLAY_H
#define MONITOR_DISPLAY_H

#include <iostream>
#include <subsystems/subsystemBase.h>
#include <subsystems/hardwareBase.h>

class Display : public SubsystemBase {
public:
    class DisplayHardware : public HardwareBase {
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
