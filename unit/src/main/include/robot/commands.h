#ifndef MONITOR_COMMANDS_H
#define MONITOR_COMMANDS_H

#include <vector>
#include <config/constants.h>

class Commands {
public:
    Commands() {};

    static Commands *instance();

    // Vision

    enum VisionState {
        STREAMING, STOPPED
    };
    enum DisplayState {
        MESH, CAMERA_IMG, UNDISTORTED_IMG, PLOTTER
    };

    VisionState visionWantedState;
    std::vector<DisplayState> displayWantedStates;

    // Uploading
    bool uploadValues[constants::general::kNumMeasurements] = { true, false, true, false, true, false, true, false };

private:
    static inline Commands *pInstance = nullptr;
};

#endif //MONITOR_COMMANDS_H