#include <subsystems/general.h>
#include <config/constants.h>
#include <utils/utils.h>

General::General(State* state) {
//    state->initTimeS = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    state->initTimeS = 0;
}

void General::read(State *state) {
//    state->timeS = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
// TODO: dont do this
    state->timeS += 1;
}

void General::calculate(State *state, Commands *commands, Outputs *outputs) {
}

void General::write(Outputs *outputs) {
}

General *General::instance(State *state) {
    if (General::pInstance == nullptr) {
        General::pInstance = new General(state);
    }
    return General::pInstance;
}

std::string General::name() {
    return std::string("general");
}


