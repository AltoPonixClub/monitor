#ifndef MONITOR_ROUTINEBASE_H
#define MONITOR_ROUTINEBASE_H


#include <string>

class RoutineBase {
public:
    enum State {
        RUNNING,
        FINISHED
    };
    RoutineBase();
    virtual void update() = 0;
    virtual bool isFinished() = 0;
    virtual std::string name() = 0;
};


#endif //MONITOR_ROUTINEBASE_H
