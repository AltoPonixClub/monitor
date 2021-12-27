#ifndef MONITOR_GENERAL_H
#define MONITOR_GENERAL_H

#include <iostream>
#include <subsystems/subsystemBase.h>
#include <opencv2/opencv.hpp>
#include <opencv2/aruco/dictionary.hpp>
#include <opencv2/aruco.hpp>
#include <config/constants.h>

class General : public SubsystemBase {
public:
    General(State *state);

    void read(State *state);

    void calculate(State *state, Commands *commands, Outputs *outputs);

    void write(Outputs *outputs);

    static General *instance(State* state);

    std::string name();

private:
    static inline General *pInstance = nullptr;
};

#endif //MONITOR_GENERAL_H
