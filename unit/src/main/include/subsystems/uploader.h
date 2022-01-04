//
// Created by Lucas on 1/1/22.
//

#ifndef MONITOR_UPLOADER_H
#define MONITOR_UPLOADER_H

#import <subsystems/subsystemBase.h>

class Uploader : public SubsystemBase {
public:
    Uploader(State *state, Commands *commands, Outputs *outputs);

    void read(State *state);

    void calculate(State *state, Commands *commands, Outputs *outputs);

    void write(Outputs *outputs);

    static Uploader *instance(State *state, Commands *commands, Outputs *outputs);

    std::string name();

private:

    static inline Uploader *pInstance = nullptr;

    float State::*measurementPointers[8];

    long lastUploadTimes[8] = { 0 };
};

#endif //MONITOR_UPLOADER_H
