
#include "subsystems/threadedBase.h"

ThreadedBase::ThreadedBase(SubsystemBase *subsystem, State *state, Commands *commands, Outputs *outputs) {
    this->subsystem = subsystem;
    this->state = state;
    this->commands = commands;
    this->outputs = outputs;
}
void ThreadedBase::run() {
    while (1) {
        this->subsystem->read(state);
        this->subsystem->calculate(state, commands, outputs);
        this->subsystem->write(outputs);
    }
}


