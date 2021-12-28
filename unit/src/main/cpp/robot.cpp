#include <iostream>
#include <robot/state.h>
#include <robot/control.h>
#include <subsystems/subsystemBase.h>
#include <subsystems/vision.h>
#include <subsystems/display.h>
#include <subsystems/general.h>

int main() {
    std::cout << "started" << std::endl;
    State *state = State::instance();
    std::cout << "started" << std::endl;
    Commands *commands = Commands::instance();
    std::cout << "started" << std::endl;
    Outputs *outputs = Outputs::instance();
    std::cout << "started" << std::endl;
    Control::configure(commands);
    std::cout << "started" << std::endl;
    std::vector<SubsystemBase *> enabledSubsystems{General::instance(state), Vision::instance(state, commands, outputs), Display::instance(state, commands, outputs)};
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
