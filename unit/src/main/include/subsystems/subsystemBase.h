#ifndef MONITOR_SUBSYSTEMBASE_H
#define MONITOR_SUBSYSTEMBASE_H

#include <iostream>
#include <robot/robotState.h>
#include <robot/outputs.h>
#include <robot/commands.h>

class SubsystemBase {
public:
    class HardwareBase {
    public:

        virtual void configure() = 0;

        virtual void read(RobotState *state) = 0;

        virtual void write(Outputs *outputs) = 0;

        static HardwareBase *instance();
    };

    // TODO: read and write are pretty stupid
    virtual void calculate(RobotState *state, Commands *commands, Outputs *outputs) = 0;

    static SubsystemBase *instance();

    virtual std::string name() = 0;
};

#endif //MONITOR_SUBSYSTEMBASE_H
