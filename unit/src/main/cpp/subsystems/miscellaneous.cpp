#include <config/configs.h>
#include <subsystems/miscellaneous.h>

Miscellaneous::Miscellaneous(State *state) {
    //    state->initTimeS =
    //    std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    state->initTimeS = 0;
}

void Miscellaneous::read(State *state) {
    //    state->timeS =
    //    std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    // TODO: dont do this
    state->timeS += 1;
    // do fps etc
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

std::string Miscellaneous::name() { return std::string("general"); }
