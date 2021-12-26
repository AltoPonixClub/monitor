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

// TODO: Move commands to all functions
Display::Display() {
    std::cout << "Display Hardware Initialized" << std::endl;

    pangolin::CreateWindowAndBind("Main", constants::display::kDispSize.width, constants::display::kDispSize.height);
    glEnable(GL_DEPTH_TEST);

    // viewing state of virtual camera for rendering scene; intrinsics and extrinsics
    this->sCam = pangolin::OpenGlRenderState(
            pangolin::ProjectionMatrix(640, 480, 420, 420, 320, 240, 0.2, 100),
            pangolin::ModelViewLookAt(constants::physical::kPlatformDim.width / 2, -15, 10,
                                      constants::physical::kPlatformDim.width / 2,
                                      constants::physical::kPlatformDim.height / 2, 0, pangolin::AxisZ));

//    pangolin::View& dCam = pangolin::CreateDisplay().SetBounds(0.0, 1.0, 0.0, 1.0, -640.0f / 480.0f).SetHandler(new pangolin::Handler3D(this->sCam));
    this->dCam = pangolin::CreateDisplay().SetBounds(0.0, 1.0, 0.0, 1.0, -640.0f / 480.0f).SetHandler(
            new pangolin::Handler3D(this->sCam));
//     Create Interactive View in window

//     Set up plotter
//
//    const float tinc = 0.01f;
//    pangolin::Plotter plotter(&this->log, 0.0f, 4.0f * (float) M_PI / tinc - 2.0f, -5, 30, 0.5f);
//    plotter.SetBounds(0, 0.3, 0.0, 0.33);
//    plotter.Track("$i");
//    pangolin::DisplayBase().AddDisplay(plotter);

//    this->log = pangolin::DataLog();
//    std::vector<std::string> labels{"tvec[0]"};
//    this->log.SetLabels(labels);

    this->dImg = pangolin::Display("image").SetBounds(2.0 / 3, 1.0, 0, 3 / 10.f,
                                                      (float) constants::display::kImgDispSize.width /
                                                      (float) constants::display::kImgDispSize.height).SetLock(
            pangolin::LockLeft, pangolin::LockTop);
//
}

void Display::read(State *state) {
}

void Display::calculate(State *state, Commands *commands, Outputs *outputs) {
//    outputs->displayFrame = state->undistortedFrame.empty() ? cv::Mat(constants::physical::kImgSize.height,
//                                                                      constants::physical::kImgSize.width, CV_8UC3,
//                                                                      cv::Scalar(100, 100, 100))
//                                                            : state->undistortedFrame;
    Eigen::Matrix4f transformationMatrix;

    /*
    * Translation Matrix
    * [ 1 0 0 X ]
    * [ 0 1 0 Y ]
    * [ 0 0 1 Z ]
    * [ 0 0 0 1 ]
    */
//    transformationMatrix << 1, 0, 0, state->cam_tvec[0] + constants::physical::kPlatformDim.height / 2,
//            0, 1, 0, state->cam_tvec[1] + constants::physical::kPlatformDim.width / 2,
//            0, 0, 1, state->cam_tvec[2],
//            0, 0, 0, 1;
//
//    for (auto &vertex: outputs->frustumVerts) {
//        vertex = transformationMatrix * vertex;
//    }
    cv::vconcat(state->capFrame, state->undistortedFrame, outputs->displayFrame);
    cv::flip(outputs->displayFrame, outputs->displayFrame, 0);
    cv::resize(outputs->displayFrame, outputs->displayFrame, constants::display::kImgDispSize);

    outputs->logVal = state->cam_tvec[0];
}

void Display::write(Outputs *outputs) {
    if (!pangolin::ShouldQuit()) {

        // TODO: why does split declaration and assignment here not work!!? haunted? yes
        pangolin::GlTexture imgTex = pangolin::GlTexture(constants::display::kImgDispSize.width,
                                                         constants::display::kImgDispSize.height, GL_RGB, false, 0,
                                                         GL_RGB,
                                                         GL_UNSIGNED_BYTE); // TODO: MOVE THIS OUT MAKES SLOWER PRLLY
        // Clear screen and activate view to render into
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        this->dCam.Activate(this->sCam);

        // Draws Platform
        glColor4f(1, 1, 1, 1);
        pangolin::glDrawLine(0, 0, 0, constants::physical::kPlatformDim.width, 0, 0);
        pangolin::glDrawLine(0, 0, 0, 0, constants::physical::kPlatformDim.height, 0);
        pangolin::glDrawLine(constants::physical::kPlatformDim.width, 0, 0, constants::physical::kPlatformDim.width,
                             constants::physical::kPlatformDim.height, 0);
        pangolin::glDrawLine(0, constants::physical::kPlatformDim.height, 0, constants::physical::kPlatformDim.width,
                             constants::physical::kPlatformDim.height, 0);

        // Draws Camera Frustum
        glColor4f(1.0f, 0.0f, 0.0f, 1.0f);

        // TODO: check w element of matrix is 1
        Utils::drawFrustum(outputs->frustumVerts);
        glColor3f(1, 1, 1);

        imgTex.Upload(outputs->displayFrame.data, GL_BGR,
                      GL_UNSIGNED_BYTE);
        this->dImg.Activate();
        imgTex.RenderToViewport();

        // Plotter log
        log.Log(outputs->logVal); // TODO: outputs since tvec is an output to show

        // Swap frames and Process Events
        pangolin::FinishFrame();
    }
//    cv::imshow("Window", outputs->displayFrame);
//    cv::waitKey(1);
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

