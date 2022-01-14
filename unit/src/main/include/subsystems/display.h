#ifndef MONITOR_DISPLAY_H
#define MONITOR_DISPLAY_H

#include <iostream>
#include <pangolin/handler/handler.h>
#include <pangolin/plot/datalog.h>
#include <pangolin/plot/plotter.h>
#include <subsystems/subsystemBase.h>

class Display : public SubsystemBase {
  public:
    Display(State *state, Commands *commands, Outputs *outputs);

    void read(State *state);

    void calculate(State *state, Commands *commands, Outputs *outputs);

    void write(Outputs *outputs);

    static Display *instance(State *state, Commands *commands,
                             Outputs *outputs);

    std::string name();

  private:
    pangolin::OpenGlRenderState sCam;
    pangolin::View dCam;
    pangolin::DataLog log;
    pangolin::View *dImg;
    pangolin::Plotter *plotter;

    static inline Display *pInstance = nullptr;
};

#endif // MONITOR_DISPLAY_H
