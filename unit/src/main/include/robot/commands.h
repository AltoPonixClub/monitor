#ifndef MONITOR_COMMANDS_H
#define MONITOR_COMMANDS_H

#include <vector>
#include <config/constants.h>

class Commands {
public:
    Commands() {};

    static Commands *instance();

    enum VisionState {
        MONOCULAR, STEREO, OFF
    };
    enum DisplayState {
        MESH, DISPLAY_IMG, PLOTTER, CAMERA_POS, MENU
    };
    enum UploadState {
        ATMOSPHERIC_TEMP,
        RESERVOIR_TEMP,
        LIGHT_INTENSITY,
        SOIL_MOISTURE,
        ELECTRICAL_CONDUCTIVITY,
        PH,
        DISSOLVED_OXYGEN,
        AIR_FLOW,
    };

    VisionState visionWantedState;
    std::vector<DisplayState> displayWantedStates;

    std::vector<std::pair <UploadState, long long>> uploadWantedStates;

private:
    static inline Commands *pInstance = nullptr;
};

#endif //MONITOR_COMMANDS_H