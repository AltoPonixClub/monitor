#include <robot/control.h>

// TODO : clean up vectors
void Control::configure(Commands *commands) {
    commands->visionWantedState = Commands::VisionState::MONOCULAR;
    commands->displayWantedStates = std::vector<Commands::DisplayState>{Commands::DisplayState::MESH, Commands::DisplayState::CAMERA_POS,
                                                                        Commands::DisplayState::DISPLAY_IMG};
    commands->ledWantedState = Commands::LEDState::MEDIUM;
}

void Control::update(Commands *commands) {
}

