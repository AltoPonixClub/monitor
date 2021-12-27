#ifndef MONITOR_COMMANDS_H
#define MONITOR_COMMANDS_H

#include <vector>

class Commands {
public:
    Commands() {};

    static Commands *instance();

    enum VisionState {
        STREAMING, STOPPED
    };
    enum DisplayState {
        MESH, CAMERA_IMG, UNDISTORTED_IMG, PLOTTER
    };

    VisionState visionWantedState;
    std::vector<DisplayState> displayWantedStates;
private:
    static inline Commands *pInstance = nullptr;
};

#endif //MONITOR_COMMANDS_H
