#include <robot/commands.h>

Commands::Commands() {
    this->visionWantedState = Commands::VisionState::STREAMING;
}

Commands *Commands::instance() {
    if (Commands::pInstance == nullptr) {
        Commands::pInstance = new Commands();
    }
    return Commands::pInstance;
}

