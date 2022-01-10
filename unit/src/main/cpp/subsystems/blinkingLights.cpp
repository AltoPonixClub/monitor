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

void BlinkingLights::read(State *state) {
  //    state->timeS = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
  // TODO: dont do this
  state->timeS += 1;
}

void BlinkingLights::calculate(State *state, Commands *commands, Outputs *outputs) {
}

void BlinkingLights::write(Outputs *outputs) {
}

BlinkingLights *BlinkingLights::instance(State *state) {
  if (BlinkingLights::pInstance == nullptr) {
    BlinkingLights::pInstance = new BlinkingLights(state);
  }
  return BlinkingLights::pInstance;
}

std::string BlinkingLights::name() {
  return std::string("blinkingLights");
}


