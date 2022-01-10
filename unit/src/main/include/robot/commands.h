#ifndef MONITOR_COMMANDS_H
#define MONITOR_COMMANDS_H

#include <vector>

class Commands {
  public:
    Commands(){};

    static Commands *instance();

    enum VisionState { MONOCULAR, STEREO, OFF };
    enum DisplayState { MESH, DISPLAY_IMG, PLOTTER, CAMERA_POS, MENU };

    VisionState visionWantedState;
    std::vector<DisplayState> displayWantedStates;

  private:
    static inline Commands *pInstance = nullptr;
};

#endif // MONITOR_COMMANDS_H
