#include <robot/control.h>

// TODO : clean up vectors
void Control::configure(Commands *commands) {
    commands->visionWantedState = commands->STOPPED;
    commands->displayWantedStates = std::vector<Commands::DisplayState> {commands->MESH, commands->CAMERA_IMG, commands->UNDISTORTED_IMG};
}

void Control::update(Commands *commands) {
    commands->visionWantedState = commands->STREAMING;
}


