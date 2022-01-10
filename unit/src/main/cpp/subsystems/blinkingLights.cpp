//
// Created by Maxwell Zhang on 1/9/22.
//

#include <subsystems/vision.h>
#include <config/configs.h>
#include <utils/utils.h>
#include <spdlog/spdlog.h>
#include "subsystems/blinkingLights.h"

BlinkingLights::BlinkingLights(State *state, Commands *commands, Outputs *outputs) {
    switch (commands->ledWantedState) {
    case Commands::LEDState::NOENERGY:
        break;
    case Commands::LEDState::SLOW:
        break;
    case Commands::LEDState::MEDIUM:
        break;
    case Commands::LEDState::FAST:
        break;
    }
    spdlog::info("Blinking LEDs: Successful Initialization");
}