#include <robot/control.h>
#include <robot/state.h>

// TODO : clean up vectors
void Control::configure(Commands *commands) {
    commands->visionWantedState = Commands::VisionState::MONOCULAR;
    commands->displayWantedStates = std::vector<Commands::DisplayState>{Commands::DisplayState::MESH, Commands::DisplayState::CAMERA_POS,
                                                                        Commands::DisplayState::DISPLAY_IMG};
    commands->ledWantedState = Commands::LEDState::MEDIUM;
    commands->uploadWantedStates =
        std::vector<std::pair<Commands::UploadState, long long>>{
            // std::make_pair(Commands::UploadState::PH, 1000 * 15),
            // std::make_pair(Commands::UploadState::LIGHT_INTENSITY,
            // 100 * 15)
        };
}

void Control::update(Commands *commands) {
}

