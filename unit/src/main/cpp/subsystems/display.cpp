#include <subsystems/display.h>
#include <config/constants.h>
#include <utils/utils.h>
#include <opencv2/core/eigen.hpp>

#include <pangolin/display/display.h>
#include <pangolin/display/view.h>
#include <pangolin/handler/handler.h>
#include <pangolin/gl/gl.h>
#include <pangolin/gl/glinclude.h>
#include <pangolin/gl/gldraw.h>
#include <pangolin/var/var.h>
#include <pangolin/plot/plotter.h>

#include <Eigen/Core>
#include <spdlog/spdlog.h>

// TODO: do based on commands wants
Display::Display(State *state, Commands *commands, Outputs *outputs) {

    pangolin::CreateWindowAndBind("Main", constants::display::kDispSize.width, constants::display::kDispSize.height);
    glEnable(GL_DEPTH_TEST);

    // viewing state of virtual camera for rendering scene; intrinsics and extrinsics
    this->sCam = pangolin::OpenGlRenderState(
            pangolin::ProjectionMatrix(640, 480, 420, 420, 320, 240, 0.2, 1000),
            pangolin::ModelViewLookAt(constants::physical::kPlatformDim.width / 2, -30, 75,
                                      constants::physical::kPlatformDim.width / 2,
                                      constants::physical::kPlatformDim.height / 2, 0, pangolin::AxisZ));


//    pangolin::View& dCam = pangolin::CreateDisplay().SetBounds(0.0, 1.0, 0.0, 1.0, -640.0f / 480.0f).SetHandler(new pangolin::Handler3D(this->sCam));
    this->dCam = pangolin::CreateDisplay().SetBounds(0.0, 1.0, 0.0, 1.0, -640.0f / 480.0f).SetHandler(
            new pangolin::Handler3D(this->sCam));

//     Set up plotter
    if (std::count(commands->displayWantedStates.begin(), commands->displayWantedStates.end(), commands->PLOTTER)) {
        const float tinc = 0.01f; // TODO: move this out
        std::vector<std::string> labels{"tvec[0]"};
        this->log.SetLabels(labels);
        this->plotter = new pangolin::Plotter(&this->log, 0.0f, 4.0f * (float) M_PI / tinc - 2.0f, -5, 30, 0.5f);
        plotter->SetBounds(0, 0.3, 0.0, 0.33);
        plotter->Track("$i");
        pangolin::DisplayBase().AddDisplay(*plotter);
        outputs->logVal = 0;
    }

    if (std::count(commands->displayWantedStates.begin(), commands->displayWantedStates.end(), commands->DISPLAY_IMG)) {
        this->dImg = &pangolin::Display("image").SetBounds(2.0 / 3, 1.0, 0, 3 / 10.f,
                                                           (float) constants::display::kImgDispSize.width /
                                                           (float) constants::display::kImgDispSize.height).SetLock(
                pangolin::LockLeft, pangolin::LockTop);
        outputs->displayFrame = cv::Mat(constants::vision::kImgSize.height, constants::vision::kImgSize.width, CV_8UC3,
                                        cv::Scalar(100, 100, 100));
    } else {
        this->dImg = nullptr;
    }
    spdlog::info("Display: Successful Initialization");
}

void Display::read(State *state) {
}
double d = 0.01;
void Display::calculate(State *state, Commands *commands, Outputs *outputs) {
    d += 0.01;
    Eigen::Matrix4f transformationMatrix;
    Eigen::Matrix4f reorientMatrix;
    /*
    * Translation Matrix
    * [ 1 0 0 X ]
    * [ 0 1 0 Y ]
    * [ 0 0 1 Z ]
    * [ 0 0 0 1 ]
     *
     * Upper 3 by 3 change to rodrigues for rotation
    */
//    Eigen::Matrix eigenMat;
//    cv::cv2eigen(state->camRotMat, eigenMat);
//    spdlog::info(Utils::matEig2str(eigenMat));

    // TODO: fix this
    // TODO: check w element of matrix is 1
//    transformationMatrix << 1, 0, 0, state->camTvec[0] + constants::physical::kPlatformDim.height / 2,
//            0, 1, 0, state->camTvec[1] + constants::physical::kPlatformDim.width / 2,
//            0, 0, 1, state->camTvec[2],
//            0, 0, 0, 1;

//    transformationMatrix << 1, 0, 0, 0,
//            0, 1, 0, 0,
//            0, 0, 1, 0,
//            0, 0, 0, 1;

// TODO: more efficient to transform just one point and move all other corners around that
//    transformationMatrix << state->camRotMat.at<float>(0, 0), state->camRotMat.at<float>(0, 1), state->camRotMat.at<float>(0, 2), state->camTvec[0] + constants::physical::kPlatformDim.height / 2,
//            state->camRotMat.at<float>(1, 0), state->camRotMat.at<float>(1, 1), state->camRotMat.at<float>(1, 2), state->camTvec[1] + constants::physical::kPlatformDim.width / 2,
//            state->camRotMat.at<float>(2, 0), state->camRotMat.at<float>(2, 1), state->camRotMat.at<float>(2, 2), state->camTvec[2],
//            0, 0, 0, 1;
    transformationMatrix << state->camRotMat.at<double>(0, 0), state->camRotMat.at<double>(0,
                                                                                           1), state->camRotMat.at<double>(
            0, 2), state->camTvec[0] + constants::physical::kPlatformDim.height / 2, // TODO: no divide by 2
            state->camRotMat.at<double>(1, 0), state->camRotMat.at<double>(1, 1), state->camRotMat.at<double>(1, 2),
            state->camTvec[1] + constants::physical::kPlatformDim.width / 2,
            state->camRotMat.at<double>(2, 0), state->camRotMat.at<double>(2, 1), state->camRotMat.at<double>(2,
                                                                                                              2), state->camTvec[2],
            0, 0, 0, 1;

    reorientMatrix << 1, 0, 0, 0,
            0, cos(Utils::deg2rad(180)), -sin(Utils::deg2rad(180)), 0,
            0, sin(Utils::deg2rad(180)), cos(Utils::deg2rad(180)), 0,
            0, 0, 0, 1;

//    transformationMatrix << 1, 0, 0, 0, // TODO: no divide by 2
//            0, 1, 0, 0,
//            0, 0, 1, 0,
//            0, 0, 0, 1;

    if (std::count(commands->displayWantedStates.begin(), commands->displayWantedStates.end(), commands->CAMERA_POS)) {
        outputs->frustumVerts = Utils::getFrustumVertices(-0.5, -0.5, 1, 1, 1, 1,
                                                          2); // TODO: this is atrocious, dont redo each loop smh
        for (auto &vertex: outputs->frustumVerts) {
            vertex = transformationMatrix * (reorientMatrix * vertex);
        }
    }


    if (std::count(commands->displayWantedStates.begin(), commands->displayWantedStates.end(), commands->DISPLAY_IMG)) {
        cv::vconcat(outputs->editedCapFrame, state->undistortedFrame, outputs->displayFrame);
        cv::flip(outputs->displayFrame, outputs->displayFrame, 0);
        cv::resize(outputs->displayFrame, outputs->displayFrame, constants::display::kImgDispSize);
    }


    if (std::count(commands->displayWantedStates.begin(), commands->displayWantedStates.end(), commands->PLOTTER)) {
        outputs->logVal = state->camTvec[0];
    }

    // Mesh Creation
    outputs->meshColor.clear();
    outputs->meshLines.clear();
    if (std::count(commands->displayWantedStates.begin(), commands->displayWantedStates.end(), commands->MESH)) {
        cv::Mat tmp; // TODO: clean up
        cv::resize(state->undistortedFrame, tmp,
                   cv::Size(constants::display::kMeshDensity, constants::display::kMeshDensity));
        for (int i = 0; i < constants::display::kMeshDensity - 1; i++) {
            for (int j = 0; j < constants::display::kMeshDensity - 1; j++) { // TODO: this wrong
                outputs->meshLines.push_back((Eigen::Matrix<float, 6, 1>()
                        << constants::physical::kPlatformDim.width * i / constants::display::kMeshDensity,
                        constants::physical::kPlatformDim.height * j /
                        constants::display::kMeshDensity, state->depthMap[int(
                        state->depthMap.size() * (i / constants::display::kMeshDensity))][int(
                        state->depthMap[0].size() * (j / constants::display::kMeshDensity))],
                        constants::physical::kPlatformDim.width * (i + 1) / constants::display::kMeshDensity,
                        constants::physical::kPlatformDim.height * (j + 1) /
                        constants::display::kMeshDensity, state->depthMap[int(
                        state->depthMap.size() * ((i + 1) / constants::display::kMeshDensity))][int(
                        state->depthMap[0].size() * ((j + 1) / constants::display::kMeshDensity))]).finished());
                outputs->meshColor.emplace_back(tmp.at<cv::Vec3b>(
                        cv::Point(i, j)));
            }
        }
    }

}
double dd = 1;
void Display::write(Outputs *outputs) {
    if (!pangolin::ShouldQuit()) {
        glClearColor(0.5, 0.7, 0.7, 0.0f); // Background Color
        glLineWidth(3);
        // TODO: why does split declaration and assignment here not work!!? haunted? yes
        pangolin::GlTexture imgTex = pangolin::GlTexture(constants::display::kImgDispSize.width,
                                                         constants::display::kImgDispSize.height, GL_RGB, false, 0,
                                                         GL_RGB,
                                                         GL_UNSIGNED_BYTE); // TODO: MOVE THIS OUT MAKES SLOWER PRLLY
        // Clear screen and activate view to render into
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        this->sCam = pangolin::OpenGlRenderState(
//                pangolin::ProjectionMatrix(640, 480, 420, 420, 320, 240, 0.2, 1000),
//                pangolin::ModelViewLookAt(constants::physical::kPlatformDim.width / 2, -30, 75 + dd,
//                                          constants::physical::kPlatformDim.width / 2,
//                                          constants::physical::kPlatformDim.height / 2, 0, pangolin::AxisZ));
//        dd -= 1;
        this->sCam = constants::vision::side3;
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
        glBegin(GL_QUADS);
        for (int i = 0; i < outputs->frustumVerts.size(); i++) {
            for (int j = i + 1; j < outputs->frustumVerts.size(); j++) {
                for (int c = j + 1; c < outputs->frustumVerts.size(); c++) {
                    glVertex3f(outputs->frustumVerts[i].data()[0], outputs->frustumVerts[i].data()[1],
                               outputs->frustumVerts[i].data()[2]);

                    glVertex3f(outputs->frustumVerts[j].data()[0], outputs->frustumVerts[j].data()[1],
                               outputs->frustumVerts[j].data()[2]);

                    glVertex3f(outputs->frustumVerts[c].data()[0], outputs->frustumVerts[c].data()[1],
                               outputs->frustumVerts[c].data()[2]);
                }
            }
        }
        glEnd();
        // TODO: a lot of this shouldnt be configured here
        glPointSize(15);
        glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
        glBegin(GL_POINTS);
        glVertex3f(outputs->frustumVerts.back().data()[0], outputs->frustumVerts.back().data()[1],
                   outputs->frustumVerts.back().data()[2]);
        glEnd();

        for (int i = 0; i < outputs->meshLines.size(); i++) {
            glColor3ub(outputs->meshColor[i][2], outputs->meshColor[i][1], outputs->meshColor[i][0]);
            pangolin::glDrawLine(outputs->meshLines[i][0], outputs->meshLines[i][1], outputs->meshLines[i][2],
                                 outputs->meshLines[i][3], outputs->meshLines[i][4], outputs->meshLines[i][5]);
        }

        glColor3f(1, 1, 1);

        if (this->dImg != nullptr) {
            imgTex.Upload(outputs->displayFrame.data, GL_BGR,
                          GL_UNSIGNED_BYTE);
            this->dImg->Activate();
            imgTex.RenderToViewport();
        }

        // Plotter log
        log.Log(outputs->logVal); // TODO: outputs since tvec is an output to show

        // Swap frames and Process Events
        pangolin::FinishFrame();
    }
}


Display *Display::instance(State *state, Commands *commands, Outputs *outputs) {
    if (Display::pInstance == nullptr) {
        Display::pInstance = new Display(state, commands, outputs);

    }
    return Display::pInstance;
}

std::string Display::name() {
    return std::string("display");
}

