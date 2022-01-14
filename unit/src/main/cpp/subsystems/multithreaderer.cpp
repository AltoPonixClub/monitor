
#include "subsystems/multithreaderer.h"
#include <thread>

Multithreader::Multithreader(std::vector<SubsystemBase *> subsystems) {
    this->subsystems = subsystems;
}

void Multithreader::loop(SubsystemBase *subsystem, State *state,
                         Commands *commands, Outputs *outputs) {
    while (true) {
        subsystem->read(state);
        subsystem->calculate(state, commands, outputs);
        subsystem->write(outputs);
    }
}

void Multithreader::start(State *state, Commands *commands, Outputs *outputs) {
    for (SubsystemBase *subsystem : subsystems) {
        threads.push_back(new std::thread(&Multithreader::loop, subsystem,
                                          state, commands, outputs));
    }
    for (auto thread : threads) {
        thread->join();
    }
}

Multithreader *
Multithreader::instance(std::vector<SubsystemBase *> subsystems) {
    if (Multithreader::pInstance == nullptr) {
        Multithreader::pInstance = new Multithreader(subsystems);
    }
    return Multithreader::pInstance;
}
