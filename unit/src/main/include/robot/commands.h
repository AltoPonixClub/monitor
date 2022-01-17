#ifndef MONITOR_COMMANDS_H
#define MONITOR_COMMANDS_H

#include <config/configs.h>
#include <vector>

class Commands {
  public:
    static Commands *instance();

    enum class VisionState { MONOCULAR, STEREO, OFF };
    enum class DisplayState { MESH, DISPLAY_IMG, PLOTTER, CAMERA_POS, MENU };

    enum class LEDState { OFF, SLOW, MEDIUM, FAST, SUPERFAST };

    // TODO: convert this to enum class
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
    LEDState ledWantedState;
    std::vector<DisplayState> displayWantedStates;

    std::vector<std::pair<UploadState, long long>> uploadWantedStates;

  private:
    Commands(){};
    static inline Commands *pInstance = nullptr;
};

#endif // MONITOR_COMMANDS_H
