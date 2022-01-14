#ifndef MONITOR_THREADERER_H
#define MONITOR_THREADERER_H

#include "robot/commands.h"
#include "robot/outputs.h"
#include "robot/state.h"
#include "subsystemBase.h"
#include <thread>
#include <vector>

class Threader {
  public:
    void start(State *state, Commands *commands, Outputs *outputs);
    static Threader *instance(std::vector<SubsystemBase *> subsystems);

  private:
    std::vector<SubsystemBase *> subsystems;
    std::vector<std::thread *> threads;
    static void loop(SubsystemBase *subsystem, State *state, Commands *commands,
                     Outputs *outputs);
    Threader(std::vector<SubsystemBase *> subsystems);
    static inline Threader *pInstance = nullptr;
};
#endif // MONITOR_THREADERER_H
