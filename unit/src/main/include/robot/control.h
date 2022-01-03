#ifndef MONITOR_CONTROL_H
#define MONITOR_CONTROL_H

#include <robot/state.h>
#include <robot/commands.h>

class Control {
public:
    static void configure(State *state, Commands *commands);

    static void update(State *state, Commands *commands);
};

#endif //MONITOR_CONTROL_H
