#include <robot/control.h>

void Control::configure(Commands *commands) {
    commands->visionWantedState = commands->STOPPED;
    commands->displayWantedState = commands->ON;
}

void Control::update(Commands *commands) {
    commands->visionWantedState = commands->STREAMING;
}


