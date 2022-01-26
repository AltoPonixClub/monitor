#ifndef MONITOR_UPLOADER_H
#define MONITOR_UPLOADER_H

#include "subsystems/subsystemBase.h"

class Uploader : public SubsystemBase {
  public:
    Uploader(State *state, Commands *commands, Outputs *outputs);

    void read(State *state, Commands *commands);

    void calculate(State *state, Commands *commands, Outputs *outputs);

    void write(Outputs *outputs);

    bool threaded();

    static Uploader *instance(State *state, Commands *commands,
                              Outputs *outputs);

    std::string name();

  private:
    static inline Uploader *pInstance = nullptr;
};

#endif // MONITOR_UPLOADER_H
