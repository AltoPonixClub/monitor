
#include <subsystems/threadedManager.h>

// TODO: finish
ThreadedManager::ThreadedManager(std::vector<ThreadedBase> threadedSystems) {
    for (auto threadedSystem : threadedSystems) {
        this->threadedSystems.push_back(std::make_pair(threadedSystem, new std::thread(&threadedSystem::run, this)));
    }
}

