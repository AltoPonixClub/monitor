#ifndef MONITOR_DISPLAY_H
#define MONITOR_DISPLAY_H

#include <iostream>
#include <subsystems/subsystemBase.h>
#include <pangolin/display/opengl_render_state.h>
#include <pangolin/handler/handler.h>
#include <pangolin/plot/datalog.h>
#include <pangolin/plot/plotter.h>

class Display : public SubsystemBase {
public:
    pangolin::OpenGlRenderState s_cam;
    pangolin::Handler3D handler;
    pangolin::View &d_cam;
    pangolin::DataLog log;
    pangolin::View &d_image;

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
