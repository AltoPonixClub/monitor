#include <robot/control.h>
#include <robot/state.h>

// TODO : clean up vectors
void Control::configure(State *state, Commands *commands) {
    commands->visionWantedState = commands->STOPPED;
    commands->displayWantedStates = std::vector<Commands::DisplayState> {commands->MESH, commands->CAMERA_IMG, commands->UNDISTORTED_IMG};

//    commands->uploadWantedStates.push_back(std::make_pair(Commands::UploadState::PH, 1000 * 15));
}

void Control::update(State *state, Commands *commands) {
    commands->visionWantedState = commands->STREAMING;
}


