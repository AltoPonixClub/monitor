#ifndef MONITOR_THREADEDMANAGER_H
#define MONITOR_THREADEDMANAGER_H

#include <vector>
#include <thread>
#include <subsystems/threadedBase.h>

class ThreadedManager {
private:
    std::vector<std::pair<ThreadedBase, std::thread>> threadedSystems;
public:
    ThreadedManager(std::vector<ThreadedBase> threadedSystems);
};
#endif //MONITOR_THREADEDMANAGER_H
