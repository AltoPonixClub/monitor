#include <iostream>
#include <subsystems/hardwareBase.h>
#include <robot/robotState.h>
#include <subsystems/subsystemBase.h>
#include <subsystems/vision.h>
#include <subsystems/display.h>

int main() {
    RobotState *state = RobotState::instance();
    Commands *commands = Commands::instance();
    Outputs *outputs = Outputs::instance();
    std::vector<SubsystemBase *> enabledSubsystems{Vision::instance(), Display::instance()};
    commands->visionWantedState = commands->STREAMING;


    for (SubsystemBase *subsystem: enabledSubsystems) {
//        subsystem->
//        configure();
    }

    while (true) {
        for (SubsystemBase *subsystem: enabledSubsystems) {
//            subsystem->read(state);
            subsystem->calculate(state, commands, outputs);
//            std::cout << state->capFrame << std::endl << std::endl;
//            subsystem->write(outputs);
        }
    }
}
