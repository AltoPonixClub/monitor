#ifndef MONITOR_MULTITHREADERER_H
#define MONITOR_MULTITHREADERER_H

#include "manager.h"
#include <thread>
#include <vector>

class Multithreader {
  public:
    void start(State *state, Commands *commands, Outputs *outputs);
    static Multithreader *instance(std::vector<SubsystemBase *> subsystems);

  private:
    std::vector<SubsystemBase *> subsystems;
    std::vector<std::thread *> threads;
    static void loop(SubsystemBase *subsystem, State *state, Commands *commands,
                     Outputs *outputs);
    Multithreader(std::vector<SubsystemBase *> subsystems);
    static inline Multithreader *pInstance = nullptr;
};
#endif // MONITOR_MULTITHREADERER_H
