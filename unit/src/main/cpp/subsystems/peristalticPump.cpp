//
// Created by Maxwell Zhang on 1/17/22.
//

#include "utils/daq.h"
#include "subsystems/peristalticPump.h"
#include <config/configs.h>
#include <spdlog/spdlog.h>
#include <subsystems/vision.h>
#include <utils/utils.h>

PeristalticPump::PeristalticPump(State *state, Commands *commands,
                                 Outputs *outputs) {
    spdlog::info("Peristaltic Pump: Successful Initialization");
    state-> buttonStateGetCommand = "/get?pin=3";
    outputs-> pumpCommand = "/post?pin=(2,0)";
}

void PeristalticPump::read(State *state) {
    state->buttonState = DAQ::instance(Configs::DAQ::kArduinoPort)->request(state -> buttonStateGetCommand);
}

void PeristalticPump::calculate(State *state, Commands *commands,
                                Outputs *outputs) {
    if (state->buttonState == "0") {
        outputs-> pumpCommand = "/post?pin=(2,0)";
    }
    else {
        outputs-> pumpCommand = "/post?pin=(2,1)";
    }
}

void PeristalticPump::write(Outputs *outputs) {
    DAQ::instance(Configs::DAQ::kArduinoPort)->request(outputs->pumpCommand);
}

PeristalticPump *PeristalticPump::instance(State *state, Commands *commands,
                                           Outputs *outputs) {
    if (PeristalticPump::pInstance == nullptr) {
        PeristalticPump::pInstance =
            new PeristalticPump(state, commands, outputs);
    }
    return PeristalticPump::pInstance;
}

std::string PeristalticPump::name() { return std::string("peristalticPump"); }

bool PeristalticPump::threaded() { return false; }