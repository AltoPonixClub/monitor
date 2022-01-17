#include "robot/control.h"
#include "robot/state.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"
#include "subsystems/display.h"
#include "subsystems/miscellaneous.h"
#include "subsystems/subsystemBase.h"
#include "subsystems/threaderer.h"
#include "subsystems/uploader.h"
#include "subsystems/vision.h"
#include "config/configs.h"
#include "subsystems/blinkingLights.h"
#include "utils/daq.h"
#include <QCoreApplication>

int main(int argc, char **argv) {
    // TODO: read
    // https://github.com/stevenlovegrove/Pangolin/blob/master/examples/HelloPangolinThreads/main.cpp
    spdlog::set_default_logger(spdlog::stdout_color_mt("console"));

    QCoreApplication app(argc, argv); //use QCoreApplication::instance() to access TODO:init in subsystems

    spdlog::info("Starting robot");
    State *state = State::instance();
    Commands *commands = Commands::instance();
    Outputs *outputs = Outputs::instance();
    state->argc = argc;
    state->argv = argv;
    Configs::configure();
    Control::configure(commands);
    std::vector<SubsystemBase *> enabledSubsystems{
        Miscellaneous::instance(state),
        Vision::instance(state, commands, outputs),
        Display::instance(state, commands, outputs),
        BlinkingLights::instance(state, commands, outputs),
        Uploader::instance(state, commands,
                           outputs) // TODO: why cant uploader be threaded
    };

    std::vector<SubsystemBase *> threadedSubsystems, nonThreadedSubsystems;
    for (SubsystemBase *subsystem : enabledSubsystems) {
        if (subsystem->threaded())
            threadedSubsystems.push_back(subsystem);
        else
            nonThreadedSubsystems.push_back(subsystem);
    }

    spdlog::info("X Threaded Started: " +
                 std::to_string(threadedSubsystems.size()));

    spdlog::info("Finished initialization");

    Threader *threader = Threader::instance(threadedSubsystems);
    threader->start(state, commands, outputs);
    // TODO: update control in separate thread
    while (true) {
        Control::update(commands);
        for (SubsystemBase *subsystem : nonThreadedSubsystems) {
            subsystem->read(state);
            subsystem->calculate(state, commands, outputs);
            subsystem->write(outputs);
        }
    }
}