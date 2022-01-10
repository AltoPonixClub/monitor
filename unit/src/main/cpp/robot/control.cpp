#include <robot/control.h>
#include <robot/state.h>

// TODO : clean up vectors
void Control::configure(Commands *commands) {
    commands->visionWantedState = commands->MONOCULAR;
    commands->displayWantedStates = std::vector<Commands::DisplayState>{commands->MESH, commands->CAMERA_POS,
                                                                        commands->DISPLAY_IMG};
    commands->uploadWantedStates.push_back(std::make_pair(Commands::UploadState::PH, 1000 * 15));
}

void Control::update(Commands *commands) {
}


