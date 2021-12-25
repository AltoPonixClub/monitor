#ifndef MONITOR_DISPLAY_H
#define MONITOR_DISPLAY_H

#include <iostream>
#include <subsystems/subsystemBase.h>

#include <pangolin/display/display.h>
#include <pangolin/display/view.h>
#include <pangolin/handler/handler.h>
#include <pangolin/gl/gl.h>
#include <pangolin/gl/glinclude.h>
#include <pangolin/display/opengl_render_state.h>
#include <pangolin/gl/gldraw.h>
#include <pangolin/video/video_input.h>
#include <pangolin/gl/glformattraits.h>
#include <pangolin/var/var.h>
#include <pangolin/var/varextra.h>
#include <pangolin/plot/plotter.h>

#include <Eigen/Core>


class Display : public SubsystemBase {
public:
    void configure();

    void read(RobotState *state);

    void write(Outputs *outputs);

    void calculate(RobotState *state, Commands *commands, Outputs *outputs);

    static Display *instance();

    std::string name();

private:
    static inline Display *pInstance = nullptr;
};

#endif //MONITOR_DISPLAY_H
