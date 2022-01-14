
#include "subsystems/manager.h"

Manager::Manager(SubsystemBase *subsystem) { this->subsystem = subsystem; };

void Manager::loop(State *state, Commands *commands, Outputs *outputs) {
    while (true) {
        subsystem->read(state);
        subsystem->calculate(state, commands, outputs);
        subsystem->write(outputs);
    }
}
