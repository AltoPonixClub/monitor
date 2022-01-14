#ifndef MONITOR_MANAGER_H
#define MONITOR_MANAGER_H

#include "subsystemBase.h"

class Manager {
  public:
    Manager(SubsystemBase *subsystems);

  private:
    SubsystemBase *subsystem;
    void loop(State *state, Commands *commands, Outputs *outputs);
};
#endif // MONITOR_MANAGER_H
