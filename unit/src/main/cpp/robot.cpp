#include <iostream>
#include <robot/state.h>
#include <robot/control.h>
#include <subsystems/subsystemBase.h>
#include <subsystems/vision.h>
#include <subsystems/display.h>
#include <subsystems/general.h>
#include "robot/daq.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <QCoreApplication>

int main(int argc, char** argv) {
    auto logger = spdlog::stdout_color_mt("console");
    spdlog::set_default_logger(logger);

    QCoreApplication app(argc, argv);

    spdlog::info("Starting robot");
    State *state = State::instance();
    Commands *commands = Commands::instance();
    Outputs *outputs = Outputs::instance();
    DAQ *daq = DAQ::instance("cu.usbmodem13401");
    Control::configure(commands);
    std::vector<SubsystemBase *> enabledSubsystems{General::instance(state), Vision::instance(state, commands, outputs), Display::instance(state, commands, outputs)};
    spdlog::info("Finished initialization");

    while (true) {
        Control::update(commands);
        for (SubsystemBase *subsystem: enabledSubsystems) {
            subsystem->read(state);
            subsystem->calculate(state, commands, outputs);
            subsystem->write(outputs);
        }
    }
}
