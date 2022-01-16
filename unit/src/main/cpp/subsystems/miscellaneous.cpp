#include <config/configs.h>
#include <subsystems/miscellaneous.h>
#include <utils/utils.h>

Miscellaneous::Miscellaneous(State *state) {
    //    state->initTimeS =
    //    std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    state->initTimeS = Utils::getUnixTimestamp();
}

void Miscellaneous::read(State *state) {
    state->timeS = Utils::getUnixTimestamp();
}

void Miscellaneous::calculate(State *state, Commands *commands,
                              Outputs *outputs) {}

void Miscellaneous::write(Outputs *outputs) {}

Miscellaneous *Miscellaneous::instance(State *state) {
    if (Miscellaneous::pInstance == nullptr) {
        Miscellaneous::pInstance = new Miscellaneous(state);
    }
    return Miscellaneous::pInstance;
}

std::string Miscellaneous::name() { return "general"; }

bool Miscellaneous::threaded() {
    return true;
}
