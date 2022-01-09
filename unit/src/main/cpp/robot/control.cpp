#include <robot/control.h>

// TODO : clean up vectors
void Control::configure(Commands *commands) {
    commands->visionWantedState = commands->MONOCULAR;
    commands->displayWantedStates = std::vector<Commands::DisplayState>{commands->MESH, commands->CAMERA_POS,
                                                                        commands->DISPLAY_IMG};
}

void Control::update(Commands *commands) {
}


