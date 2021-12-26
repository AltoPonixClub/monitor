#include <subsystems/display.h>
#include <config/constants.h>
#include <utils/utils.h>

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

Display::Display() {
    std::cout << "Display Hardware Initialized" << std::endl;

    pangolin::CreateWindowAndBind("Main", constants::display::dispSize.width, constants::display::dispSize.height);
    glEnable(GL_DEPTH_TEST);

    // viewing state of virtual camera for rendering scene; intrinsics and extrinsics
    this->s_cam = pangolin::OpenGlRenderState(
            pangolin::ProjectionMatrix(640, 480, 420, 420, 320, 240, 0.2, 100),
            pangolin::ModelViewLookAt(constants::vision::platformDim.width / 2, -15, 10,
                                      constants::vision::platformDim.width / 2,
                                      constants::vision::platformDim.height / 2, 0, pangolin::AxisZ));

//     Create Interactive View in window
//

    pangolin::Handler3D handler(this->s_cam);
    this->d_cam = pangolin::CreateDisplay().SetBounds(0.0, 1.0, 0.0, 1.0, -640.0f / 480.0f).SetHandler(&handler);
//
//     Set up plotter
    const float tinc = 0.01f; // TODO: move this tf out
    pangolin::Plotter plotter(&log, 0.0f, 4.0f * (float) M_PI / tinc - 2.0f, -5, 30, 0.5f);
    plotter.SetBounds(0, 0.3, 0.0, 0.33);
    plotter.Track("$i");
    pangolin::DisplayBase().AddDisplay(plotter);
    std::vector<std::string> labels{"tvec[0]"};
    this->log.SetLabels(labels);
    this->d_image = pangolin::Display("image").SetBounds(2.0 / 3, 1.0, 0, 3 / 10.f,
                                                   (float) constants::display::imgDispSize.width /
                                                   (float) constants::display::imgDispSize.height).SetLock(
            pangolin::LockLeft, pangolin::LockTop);
}

void Display::read(State *state) {
}

void Display::write(Outputs *outputs) {
    cv::imshow("Window", outputs->displayImg);
    cv::waitKey(1);
}

void Display::calculate(State *state, Commands *commands, Outputs *outputs) {
    outputs->displayImg = state->undistortedFrame.empty() ? cv::Mat(constants::vision::imgSize.height,
                                                                    constants::vision::imgSize.width, CV_8UC3,
                                                                    cv::Scalar(100, 100, 100))
                                                          : state->undistortedFrame;
}

Display *Display::instance() {
    if (Display::pInstance == nullptr) {
        Display::pInstance = new Display();

    }
    return Display::pInstance;
}

std::string Display::name() {
    return std::string("display");
}

