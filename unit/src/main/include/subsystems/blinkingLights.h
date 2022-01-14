//
// Created by Maxwell Zhang on 1/9/22.
//

#ifndef MONITOR_BLINKINGLED_H
#define MONITOR_BLINKINGLED_H

#include <iostream>
#include <subsystems/subsystemBase.h>
#include <opencv2/opencv.hpp>
#include <opencv2/aruco/dictionary.hpp>
#include <opencv2/aruco.hpp>
#include <config/configs.h>

class BlinkingLights : public SubsystemBase {
public:
  BlinkingLights(State *state, Commands *commands, Outputs *outputs);

  void read(State *state);

  void calculate(State *state, Commands *commands, Outputs *outputs);

  void write(Outputs *outputs);

  static BlinkingLights *instance(State *state, Commands *commands, Outputs *outputs);

  std::string name();

private:
  static inline BlinkingLights *pInstance = nullptr;
};

#endif //MONITOR_BLINKINGLED_H
