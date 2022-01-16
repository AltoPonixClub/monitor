#ifndef MONITOR_SUBSYSTEMBASE_H
#define MONITOR_SUBSYSTEMBASE_H

#include <iostream>
#include <robot/commands.h>
#include <robot/outputs.h>
#include <robot/state.h>

class SubsystemBase {
  public:
    virtual void read(State *state) = 0;

    virtual void calculate(State *state, Commands *commands,
                           Outputs *outputs) = 0;

    virtual void write(Outputs *outputs) = 0;

    virtual bool threaded() = 0;

    static SubsystemBase *instance(State *state);

    virtual std::string name() = 0;
  private:
    virtual void initState(State *state) = 0;
    virtual void initOutputs(Outputs *outputs) = 0;
};

#endif // MONITOR_SUBSYSTEMBASE_H
