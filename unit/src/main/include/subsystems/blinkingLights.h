//
// Created by Maxwell Zhang on 1/9/22.
//

#ifndef MONITOR_MISCELLANEOUS_H
#define MONITOR_MISCELLANEOUS_H

#include <iostream>
#include <subsystems/subsystemBase.h>
#include <opencv2/opencv.hpp>
#include <opencv2/aruco/dictionary.hpp>
#include <opencv2/aruco.hpp>
#include <config/configs.h>

class BlinkingLights : public SubsystemBase {
public:
  BlinkingLights(State *state, Commands *commands, Outputs *outputs)

  void write(Outputs *outputs);

  static BlinkingLights *instance(State *state);

  std::string name();

private:
  static inline BlinkingLights *pInstance = nullptr;
};


#endif // MONITOR_BLINKINGLIGHTS_H
