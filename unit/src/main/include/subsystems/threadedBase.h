#ifndef MONITOR_THREADEDBASE_H
#define MONITOR_THREADEDBASE_H

#include <subsystems/subsystemBase.h>

class ThreadedBase {
private:
    SubsystemBase* subsystem;
    State *state;
    Commands *commands;
    Outputs* outputs;
public:
    ThreadedBase(SubsystemBase* subsystem, State *state, Commands *commands, Outputs *outputs);
    void run();
};

#endif //MONITOR_THREADEDBASE_H
