#include <iostream>
#include <robot/robotState.h>
#include <subsystems/subsystemBase.h>
#include <subsystems/vision.h>
#include <subsystems/display.h>
#include <utils/utils.h>

int main() {
    RobotState *state = RobotState::instance();
    Commands *commands = Commands::instance();
    Outputs *outputs = Outputs::instance();
    std::vector<SubsystemBase *> enabledSubsystems{Vision::instance(), Display::instance()}; // Order might matter
    commands->visionWantedState = commands->STREAMING;

    for (SubsystemBase *subsystem: enabledSubsystems) {
        subsystem->configure();
    }

    std::cout << "Finished Initializations" << std::endl;

    while (true) {
        for (SubsystemBase *subsystem: enabledSubsystems) {
            subsystem->read(state);
            std::cout << "Finished Reading" << std::endl;
            subsystem->calculate(state, commands, outputs);
            std::cout << "Finished Calculating" << std::endl;
            subsystem->write(outputs);
            std::cout << "Finished Writing" << std::endl;
        }
        std::cout << Utils::vec2str(state->detectedArucoIds) << std::endl;
    }
}
