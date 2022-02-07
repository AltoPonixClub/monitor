
#ifndef MONITOR_ROUTINERER_H
#define MONITOR_ROUTINERER_H

#include "routineBase.h"

class Routinerer {
    void add();
    void update();
    static Routinerer *instance();
    void toString();
};

#endif //MONITOR_ROUTINERER_H
