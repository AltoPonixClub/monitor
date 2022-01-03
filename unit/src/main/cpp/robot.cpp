#include <iostream>
#include <robot/state.h>
#include <robot/control.h>
#include <subsystems/subsystemBase.h>
#include <subsystems/vision.h>
#include <subsystems/display.h>
#include <subsystems/general.h>
#include <subsystems/uploader.h>
#include <spdlog/spdlog.h>

// TODO: threading
// TODO: friend class cpp
int main() {
    spdlog::info("Starting robot");
    State *state = State::instance();
    Commands *commands = Commands::instance();
    Outputs *outputs = Outputs::instance();
    Control::configure(state, commands);
    std::vector<SubsystemBase *> enabledSubsystems{General::instance(state), Vision::instance(state, commands, outputs), Display::instance(state, commands, outputs), Uploader::instance(state, commands, outputs)};
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
