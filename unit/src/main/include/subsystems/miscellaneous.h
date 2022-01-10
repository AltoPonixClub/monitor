#ifndef MONITOR_MISCELLANEOUS_H
#define MONITOR_MISCELLANEOUS_H

#include <config/configs.h>
#include <iostream>
#include <opencv2/aruco.hpp>
#include <opencv2/aruco/dictionary.hpp>
#include <opencv2/opencv.hpp>
#include <subsystems/subsystemBase.h>

class Miscellaneous : public SubsystemBase {
  public:
    Miscellaneous(State *state);

    void read(State *state);

    void calculate(State *state, Commands *commands, Outputs *outputs);

    void write(Outputs *outputs);

    static Miscellaneous *instance(State *state);

    std::string name();

  private:
    static inline Miscellaneous *pInstance = nullptr;
};

#endif // MONITOR_MISCELLANEOUS_H
