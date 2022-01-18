//
// Created by Maxwell Zhang on 1/17/22.
//

#ifndef MONITOR_PERISTALTICPUMP_H
#define MONITOR_PERISTALTICPUMP_H

#include <config/configs.h>
#include <iostream>
#include <opencv2/aruco.hpp>
#include <opencv2/aruco/dictionary.hpp>
#include <opencv2/opencv.hpp>
#include <subsystems/subsystemBase.h>

class PeristalticPump : public SubsystemBase {
  public:
    PeristalticPump(State *state, Commands *commands, Outputs *outputs);

    void read(State *state);

    void calculate(State *state, Commands *commands, Outputs *outputs);

    void write(Outputs *outputs);

    static PeristalticPump *instance(State *state, Commands *commands,
                                    Outputs *outputs);

    std::string name();

    bool threaded();

  private:
    static inline PeristalticPump *pInstance = nullptr;
};

#endif // MONITOR_PERISTALTICPUMP_H
