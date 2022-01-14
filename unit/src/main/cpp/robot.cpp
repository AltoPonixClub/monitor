#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"
#include "subsystems/threaderer.h"
#include <robot/control.h>
#include <robot/state.h>
#include <subsystems/display.h>
#include <subsystems/miscellaneous.h>
#include <subsystems/subsystemBase.h>
#include <subsystems/uploader.h>
#include <subsystems/vision.h>

int main() {
    // TODO: read https://www.ybliu.com/2020/06/pangolin-2-use-threads.html
    spdlog::set_default_logger(spdlog::stdout_color_mt("console"));

    spdlog::info("Starting robot");
    State *state = State::instance();
    Commands *commands = Commands::instance();
    Outputs *outputs = Outputs::instance();
    Configs::configure();
    Control::configure(commands);
    std::vector<SubsystemBase *> enabledSubsystems{
        Miscellaneous::instance(state),
        Vision::instance(state, commands, outputs),
        //        Display::instance(state, commands, outputs)
        //        Uploader::instance(state, commands, outputs)
    };
    spdlog::info("Finished initialization");

    Threader *threader = Threader::instance(enabledSubsystems);
    threader->start(state, commands, outputs);
    // TODO: update control in separate thread
    //    while (true) {
    //        Control::update(commands);
    //        for (SubsystemBase *subsystem : enabledSubsystems) {
    //            subsystem->read(state);
    //            subsystem->calculate(state, commands, outputs);
    //            subsystem->write(outputs);
    //        }
    //    }
}