#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"
#include <robot/control.h>
#include <robot/state.h>
#include <subsystems/display.h>
#include <subsystems/miscellaneous.h>
#include <subsystems/subsystemBase.h>
#include <subsystems/vision.h>

int main() {
    auto logger = spdlog::stdout_color_mt("console");
    spdlog::set_default_logger(logger);

    spdlog::info("Starting robot");
    State *state = State::instance();
    Commands *commands = Commands::instance();
    Outputs *outputs = Outputs::instance();
    Configs::configure();
    Control::configure(commands);
    std::vector<SubsystemBase *> enabledSubsystems{
        Miscellaneous::instance(state),
        Vision::instance(state, commands, outputs),
        Display::instance(state, commands, outputs)};
    spdlog::info("Finished initialization");

    while (true) {
        Control::update(commands);
        for (SubsystemBase *subsystem : enabledSubsystems) {
            subsystem->read(state);
            subsystem->calculate(state, commands, outputs);
            subsystem->write(outputs);
        }
    }
}
