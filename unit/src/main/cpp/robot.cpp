#include "config/configs.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"
#include "subsystems/blinkingLights.h"
#include "utils/daq.h"
#include <QCoreApplication>
#include <iostream>
#include <robot/control.h>
#include <robot/state.h>
#include <subsystems/display.h>
#include <subsystems/miscellaneous.h>
#include <subsystems/subsystemBase.h>
#include <subsystems/uploader.h>
#include <subsystems/vision.h>

int main(int argc, char **argv) {
    auto logger = spdlog::stdout_color_mt("console");
    spdlog::set_default_logger(logger);

    QCoreApplication app(argc, argv);

    spdlog::info("Starting robot");
    State *state = State::instance();
    Commands *commands = Commands::instance();
    Outputs *outputs = Outputs::instance();
    Configs::configure();
    Control::configure(commands);
    std::vector<SubsystemBase *> enabledSubsystems{
        Miscellaneous::instance(state),
        Vision::instance(state, commands, outputs),
        Display::instance(state, commands, outputs),
        BlinkingLights::instance(
            state, commands,
            outputs) // Uploader::instance(state, commands, outputs)
    };
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