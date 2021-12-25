#ifndef MONITOR_SUBSYSTEMBASE_H
#define MONITOR_SUBSYSTEMBASE_H

#include <iostream>
#include <robot/state.h>
#include <robot/outputs.h>
#include <robot/commands.h>

class SubsystemBase {
public:
    virtual void read(State *state) = 0;

    virtual void write(Outputs *outputs) = 0;

    virtual void calculate(State *state, Commands *commands, Outputs *outputs) = 0;

    static SubsystemBase *instance();

    virtual std::string name() = 0;
};

#endif //MONITOR_SUBSYSTEMBASE_H
