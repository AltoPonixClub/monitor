#ifndef MONITOR_TCP_H
#define MONITOR_TCP_H

#include "subsystemBase.h"
#include <utils/zmq.h>

class TCP : public SubsystemBase {
  public:
    TCP(State *state, Commands *commands, Outputs *outputs);

    void read(State *state, Commands *commands);

    void calculate(State *state, Commands *commands, Outputs *outputs);

    void write(Outputs *outputs);

    bool threaded();

    static TCP *instance(State *state, Commands *commands, Outputs *outputs);

    std::string name();

  private:
    zmq::socket_t publisher;
    zmq::context_t context;
    static inline TCP *pInstance = nullptr;
};

#endif // MONITOR_TCP_H
