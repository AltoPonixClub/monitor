#include <robot/commands.h>

void Commands::configure() {
    Commands::visionWantedState = Commands::VisionState::STREAMING;
}

Commands *Commands::instance() {
    if (Commands::pInstance == nullptr) {
        Commands::pInstance = new Commands();
    }
    return Commands::pInstance;
}

