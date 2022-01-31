#include <robot/state.h>

State *State::instance() {
    if (State::pInstance == nullptr) {
        State::pInstance = new State();
    }
    return State::pInstance;
}
