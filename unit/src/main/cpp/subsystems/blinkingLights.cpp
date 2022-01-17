//
// Created by Maxwell Zhang on 1/9/22.
//

#include "subsystems/blinkingLights.h"
#include "utils/daq.h"
#include <config/configs.h>
#include <spdlog/spdlog.h>
#include <subsystems/vision.h>
#include <utils/utils.h>

BlinkingLights::BlinkingLights(State *state, Commands *commands,
                               Outputs *outputs) {
    outputs->ledCommand = "/post?pin(A0,255)";
    state->delayLED = 0;
    state->ledIsOn = false;
    state->nextToggleTime = 0;
    spdlog::info("Blinking LEDs: Successful Initialization");
}

void BlinkingLights::read(State *state) {}

void BlinkingLights::calculate(State *state, Commands *commands,
                               Outputs *outputs) {
    switch (commands->ledWantedState) {
    case Commands::LEDState::OFF:
        state->delayLED = 100;
        break;
    case Commands::LEDState::SLOW:
        state->delayLED = 20;
        break;
    case Commands::LEDState::MEDIUM:
        state->delayLED = 10;
        break;
    case Commands::LEDState::FAST:
        state->delayLED = 5;
        break;
    case Commands::LEDState::SUPERFAST:
        state->delayLED = 1;
        break;
    }
    if ((state->timeS - state->initTimeS) / 1000 >= state->nextToggleTime) {
        state->nextToggleTime += state->delayLED;
        if (state->ledIsOn) {
            state->ledIsOn = false;
            outputs->ledCommand = "/post?pin(A0,0)";
        } else {
            state->ledIsOn = true;
            outputs->ledCommand = "/post?pin(A0,255)";
        }
    }
}

void BlinkingLights::write(Outputs *outputs) {
    DAQ::instance(Configs::DAQ::kArduinoPort)->request(outputs->ledCommand);
}

BlinkingLights *BlinkingLights::instance(State *state, Commands *commands,
                                         Outputs *outputs) {
    if (BlinkingLights::pInstance == nullptr) {
        BlinkingLights::pInstance =
            new BlinkingLights(state, commands, outputs);
    }
    return BlinkingLights::pInstance;
}

std::string BlinkingLights::name() { return std::string("blinkingLights"); }

bool BlinkingLights::threaded() { return false; }
