
#ifndef MONITOR_BLINKINGLED_H
#define MONITOR_BLINKINGLED_H

#include "subsystems/subsystemBase.h"
#include <config/configs.h>
#include <iostream>
#include <opencv2/aruco.hpp>
#include <opencv2/aruco/dictionary.hpp>
#include <opencv2/opencv.hpp>

class BlinkingLights : public SubsystemBase {
  public:
    BlinkingLights(State *state, Commands *commands, Outputs *outputs);

    void read(State *state, Commands *commands);

    void calculate(State *state, Commands *commands, Outputs *outputs);

    void write(Outputs *outputs);

    static BlinkingLights *instance(State *state, Commands *commands,
                                    Outputs *outputs);

    std::string name();

    bool threaded();

  private:
    static inline BlinkingLights *pInstance = nullptr;
};

#endif // MONITOR_BLINKINGLED_H
