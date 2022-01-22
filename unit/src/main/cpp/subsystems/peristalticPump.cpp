//
// Created by Maxwell Zhang on 1/17/22.
//

#include "subsystems/peristalticPump.h"
#include "utils/daq.h"
#include <config/configs.h>
#include <spdlog/spdlog.h>
#include <subsystems/vision.h>
#include <utils/utils.h>

PeristalticPump::PeristalticPump(State *state, Commands *commands,
                                 Outputs *outputs) {
    spdlog::info("Peristaltic Pump: Successful Initialization");
    state->buttonStateGetCommandMotor1 = "/get?pin=2";
    outputs->pump1Command = "/post?pin=(3,0)";
    state->buttonStateGetCommandMotor1 = "/get?pin=1";
    state->buttonStateMotor1 = "0";
    state->buttonStateMotor2 = "0";
    outputs->pump2Command = "/post?pin=(4,0)";
}

void PeristalticPump::read(State *state) {
    state->buttonStateMotor1 =
        DAQ::instance(Configs::DAQ::kArduinoPort)
            ->request(state->buttonStateGetCommandMotor1);
    state->buttonStateMotor2 =
        DAQ::instance(Configs::DAQ::kArduinoPort)
            ->request(state->buttonStateGetCommandMotor2);
}

void PeristalticPump::calculate(State *state, Commands *commands,
                                Outputs *outputs) {
    if (state->buttonStateMotor1 == "0") {
        outputs->pump1Command = "/post?pin=(3,0)";
    } else {
        outputs->pump1Command = "/post?pin=(3,1)";
    }
    if (state->buttonStateMotor2 == "0") {
        outputs->pump2Command = "/post?pin=(4,0)";
    } else {
        outputs->pump2Command = "/post?pin=(4,1)";
    }
}

void PeristalticPump::write(Outputs *outputs) {
    DAQ::instance(Configs::DAQ::kArduinoPort)->request(outputs->pump1Command);
    DAQ::instance(Configs::DAQ::kArduinoPort)->request(outputs->pump2Command);
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