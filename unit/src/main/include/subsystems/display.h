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
    Display();

    void read(State *state);

    void calculate(State *state, Commands *commands, Outputs *outputs);

    void write(Outputs *outputs);

    static Display *instance();

    std::string name();

private:
    pangolin::OpenGlRenderState sCam;
    pangolin::View dCam;
    pangolin::DataLog log;
    pangolin::View dImg;
    pangolin::Plotter* plotter;

    static inline Display *pInstance = nullptr;

};

#endif //MONITOR_DISPLAY_H
