#ifndef MONITOR_COMMANDS_H
#define MONITOR_COMMANDS_H

#include <vector>

class Commands {
  public:
    Commands(){};

    static Commands *instance();

    enum class VisionState {
        MONOCULAR, STEREO, OFF
    };
    enum class DisplayState {
        MESH, DISPLAY_IMG, PLOTTER, CAMERA_POS, MENU
    };

    enum class LEDState {
        OFF, SLOW, MEDIUM, FAST
    };

    VisionState visionWantedState;
    LEDState ledWantedState;
    std::vector<DisplayState> displayWantedStates;

  private:
    static inline Commands *pInstance = nullptr;
};

#endif // MONITOR_COMMANDS_H
