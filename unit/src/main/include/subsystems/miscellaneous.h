#ifndef MONITOR_MISCELLANEOUS_H
#define MONITOR_MISCELLANEOUS_H

#include <iostream>
#include <subsystems/subsystemBase.h>
#include <opencv2/opencv.hpp>
#include <opencv2/aruco/dictionary.hpp>
#include <opencv2/aruco.hpp>
#include <config/configs.h>

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

#endif //MONITOR_MISCELLANEOUS_H
