#include <iostream>
#include <robot/state.h>
#include <robot/control.h>
#include <subsystems/subsystemBase.h>
#include <subsystems/vision.h>
#include <subsystems/display.h>
#include <subsystems/uploader.h>
#include <utils/utils.h>
#include <subsystems/miscellaneous.h>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

// TODO: threading
// TODO: friend class cpp
int main() {
    Utils::configureLogger();
    spdlog::info("Starting robot");
    State *state = State::instance();
    Commands *commands = Commands::instance();
    Outputs *outputs = Outputs::instance();
    Control::configure(state, commands);
    std::vector<SubsystemBase *> enabledSubsystems{Miscellaneous::instance(state),
                                                   Vision::instance(state, commands, outputs),
                                                   Display::instance(state, commands, outputs), 
                                                   Uploader::instance(state, commands, outputs)};
    spdlog::info("Finished initialization");

    while (true) {
        Control::update(state, commands);
        for (SubsystemBase *subsystem: enabledSubsystems) {
            subsystem->read(state);
            subsystem->calculate(state, commands, outputs);
            subsystem->write(outputs);
        }
    }
}
