
#include "subsystems/threaderer.h"
#include "subsystems/subsystemBase.h"
#include <spdlog/spdlog.h>
#include <thread>

Threader::Threader(std::vector<SubsystemBase *> subsystems) {
    this->subsystems = subsystems;
}

void Threader::loop(SubsystemBase *subsystem, State *state, Commands *commands,
                    Outputs *outputs) {
    while (true) {
        try {
            subsystem->read(state);
            subsystem->calculate(state, commands, outputs);
            subsystem->write(outputs);
        } catch (const std::exception &e) {
            spdlog::error(e.what());
        }
    }
}

void Threader::start(State *state, Commands *commands, Outputs *outputs) {
    for (SubsystemBase *subsystem : subsystems) {
        threads.push_back(new std::thread(&Threader::loop, subsystem, state,
                                          commands, outputs));
        if(threads.back()->joinable()) {
            threads.back()->detach(); // TODO: detach prevents out of scope
        }
        else {
            spdlog::error(subsystem->name() + " thread not joinable!");
        }
    }
}

Threader *Threader::instance(std::vector<SubsystemBase *> subsystems) {
    if (Threader::pInstance == nullptr) {
        Threader::pInstance = new Threader(subsystems);
    }
    return Threader::pInstance;
}
