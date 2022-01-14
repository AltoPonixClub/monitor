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
    state->prevJunctionTime = 0;
    spdlog::info("Blinking LEDs: Successful Initialization");
}

void BlinkingLights::read(State *state) {}

void BlinkingLights::calculate(State *state, Commands *commands,
                               Outputs *outputs) {
    state->prevJunctionTime ++;
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
    }
    spdlog::info(state->prevJunctionTime);
//    spdlog::info((int) (state->timeS/state->delayLED));
    //if ((int) ((state->timeS-state->initTimeS)/state->delayLED) % 2 == 0) {
    if ((int) ((state->prevJunctionTime)) % 2 == 0) {
        outputs->ledCommand = "/post?pin(A0,255)";
    }
    else {
        outputs->ledCommand = "/post?pin(A0,0)";
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
