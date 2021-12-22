#include <iostream>
#include <vector>
#include <algorithm>

#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>

#include <pangolin/display/display.h>
#include <pangolin/display/view.h>
#include <pangolin/handler/handler.h>
#include <pangolin/gl/gl.h>
#include <pangolin/gl/glinclude.h>
#include <pangolin/display/opengl_render_state.h>
#include <pangolin/gl/gldraw.h>
#include <pangolin/video/video_input.h>
#include <pangolin/gl/glformattraits.h>

#include <Eigen/Core>

#include "utils.h"
#include "constants.h"

using namespace std;

int main(int /*argc*/, char ** /*argv*/ ) {
    cv::VideoCapture cap(constants::cameraId);
    if (!cap.isOpened()) {
        cout << "Broken Camera";
        return -1;
    }
    cap.set(cv::CAP_PROP_FPS, constants::fps);
    cv::Ptr<cv::aruco::Dictionary> arucoDictionary = cv::aruco::Dictionary::get(cv::aruco::DICT_5X5_100);
    cv::Ptr<cv::aruco::DetectorParameters> arucoParams = cv::aruco::DetectorParameters::create();
    cv::FileStorage calibFile(constants::calibPath, cv::FileStorage::READ);
    cout << calibFile.isOpened() << endl;
    auto cameraMatrix = calibFile.operator[]("K").mat(); // extrinsics
    auto distCoeffs = calibFile.operator[]("D").mat(); // intrinsics
    calibFile.~FileStorage();

    cv::Ptr<cv::aruco::Board> board = cv::aruco::Board::create(constants::boardArucoPts, arucoDictionary,
                                                               constants::arucoIds);
    vector<vector<cv::Point2f>> detectedArucoCorners, rejectedArucoCorners;
    vector<int> detectedArucoIds;
    vector<cv::Point2f> transform_src;
    for (const auto &i: constants::boardArucoPts) {
        for (auto c: i) {
            transform_src.push_back(cv::Point2f(c.x * constants::imgSize.width / constants::platformDim.width,
                                                c.y * constants::imgSize.height /
                                                constants::platformDim.height)); // Multiplier to make bigger in final image
        }
    }

    cv::Vec3d rvec, tvec;

    pangolin::CreateWindowAndBind("Main", constants::dispSize.width, constants::dispSize.height);
    glEnable(GL_DEPTH_TEST);

    // viewing state of virtual camera for rendering scene; intrinsics and extrinsics
    pangolin::OpenGlRenderState s_cam(
            pangolin::ProjectionMatrix(640, 480, 420, 420, 320, 240, 0.2, 100),
            pangolin::ModelViewLookAt(constants::platformDim.width / 2, -15, 10, constants::platformDim.width / 2,
                                      constants::platformDim.height / 2, 0, pangolin::AxisZ)
    );

    // Create Interactive View in window
    pangolin::Handler3D handler(s_cam);

    // Display area for the camera
    pangolin::View &d_cam = pangolin::CreateDisplay()
            .SetBounds(0.0, 1.0, 0.0, 1.0, -640.0f / 480.0f)
            .SetHandler(&handler);

    // This view will take up no more than a third of the windows width or height, and it
    // will have a fixed aspect ratio to match the image that it will display. When fitting
    // within the specified bounds, push to the top-left (as specified by SetLock).
//    pangolin::View &d_image = pangolin::Display("image")
//            .SetBounds(2 / 3.0f, 1.0f, 0, 1 / 3.0f, 640.0 / 480)
//            .SetLock(pangolin::LockLeft, pangolin::LockTop);

    pangolin::View &d_image = pangolin::Display("image")
            .SetBounds(2.0 / 3, 1.0, 0, 3 / 10.f,
                       (float) constants::imgDispSize.width / (float) constants::imgDispSize.height)
            .SetLock(pangolin::LockLeft, pangolin::LockTop);
    cv::Mat frame, displayFrame;
    cv::Mat undistortedFrame(constants::imgSize.height, constants::imgSize.width, CV_8UC3, cv::Scalar(100, 100, 100));
    pangolin::GlTexture imageTexture(constants::imgDispSize.width, constants::imgDispSize.height, GL_RGB, false, 0,
                                     GL_RGB,
                                     GL_UNSIGNED_BYTE);
    while (!pangolin::ShouldQuit()) {
        // Clear screen and activate view to render into
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        d_cam.Activate(s_cam);

        cap >> frame;
        cv::resize(frame, frame, constants::imgSize);
        displayFrame = frame.clone();

        cv::aruco::detectMarkers(frame, arucoDictionary, detectedArucoCorners, detectedArucoIds, arucoParams,
                                 rejectedArucoCorners);
        cv::aruco::refineDetectedMarkers(frame, board, detectedArucoCorners, detectedArucoIds, rejectedArucoCorners,
                                         cameraMatrix, distCoeffs);
        for (const auto &corner: detectedArucoCorners) {
            for (auto pt: corner) {
                cv::circle(displayFrame, pt, constants::arucoCircRadius, constants::aqua, cv::FILLED);
            }
        }
        vector<cv::Point2f> transform_dst;
        if (detectedArucoIds.size() == 4) {
            vector<pair<int, vector<cv::Point2f>>> tmp_corners;
            cv::aruco::estimatePoseBoard(detectedArucoCorners, detectedArucoIds, board, cameraMatrix, distCoeffs, rvec,
                                         tvec);
            // Sets up transform dst for findHomography
            for (int i = 0; i < detectedArucoIds.size(); i++)
                tmp_corners.emplace_back(detectedArucoIds[i], detectedArucoCorners[i]);
            sort(tmp_corners.begin(), tmp_corners.end(), Utils::pairSortComparator);
            for (const auto &corner: tmp_corners) {
                for (auto pt: corner.second)
                    transform_dst.push_back(pt);
            }
            // TODO: use rodrigues on rvec and tvec to turn into projection matrix
            cout << "translation: " << tvec << endl;
        }
        try {
            /* Planar Rectification based on Aruco Markers */

            // Maps real world coords of board to those in the image
            cv::Mat H = cv::findHomography(transform_src, transform_dst, cv::RANSAC, 5);
            // Apply perspective transformation to original image
            cv::warpPerspective(displayFrame, undistortedFrame, H.inv(), constants::imgDispSize, cv::INTER_LINEAR);
            undistortedFrame = undistortedFrame(cv::Rect(0, 0, constants::imgSize.width, constants::imgSize.height));
        }
        catch (...) {
            cout << "Not Yet Found" << endl;
        }

        // Draws Platform
        glColor4f(1, 1, 1, 1);
        pangolin::glDrawLine(0, 0, 0, constants::platformDim.width, 0, 0);
        pangolin::glDrawLine(0, 0, 0, 0, constants::platformDim.height, 0);
        pangolin::glDrawLine(constants::platformDim.width, 0, 0, constants::platformDim.width,
                             constants::platformDim.height, 0);
        pangolin::glDrawLine(0, constants::platformDim.height, 0, constants::platformDim.width,
                             constants::platformDim.height, 0);

        // Draws Camera Frustum
        glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
        auto frustumVertices = Utils::getFrustumVertices(-0.5, -0.5, 1, 1, 1, 1, 0.25);
        Eigen::Matrix4f transformationMatrix;

        /*
        * Translation Matrix
        * [ 1 0 0 X ]
        * [ 0 1 0 Y ]
        * [ 0 0 1 Z ]
        * [ 0 0 0 1 ]
        */
        transformationMatrix << 1, 0, 0, 1,
                0, 1, 0, 1,
                0, 0, 1, 1,
                0, 0, 0, 1;

        for (auto &vertex: frustumVertices) {
            vertex = transformationMatrix * vertex;
        }
        Utils::drawFrustum(frustumVertices);
        glColor3f(1, 1, 1);


        cv::vconcat(displayFrame, undistortedFrame, displayFrame);
        cv::flip(displayFrame, displayFrame, 0);
        cv::resize(displayFrame, displayFrame, constants::imgDispSize);
        // TODO: plot tvec and rvec
        // TODO: point clouds
        // TODO: menu bar

        imageTexture.Upload(displayFrame.data, GL_BGR, GL_UNSIGNED_BYTE);
        d_image.Activate();
        imageTexture.RenderToViewport();

        // Swap frames and Process Events
        pangolin::FinishFrame();
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}
