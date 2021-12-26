#include <iostream>
#include <robot/state.h>
#include <robot/control.h>
#include <subsystems/subsystemBase.h>
#include <subsystems/vision.h>
#include <subsystems/display.h>

// TODO: logger as separate subsystem
int main() {
    State *state = State::instance();
    Commands *commands = Commands::instance();
    Outputs *outputs = Outputs::instance();
    std::vector<SubsystemBase *> enabledSubsystems{Vision::instance(), Display::instance()};
    Control::configure(commands);
    std::cout << "Finished Initializations" << std::endl;

    while (true) {
        Control::update(commands);
        for (SubsystemBase *subsystem: enabledSubsystems) {
            subsystem->read(state);
            subsystem->calculate(state, commands, outputs);
            subsystem->write(outputs);
        }
    }
}
