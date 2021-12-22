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
#include <pangolin/gl/glformattraits.h>
#include <pangolin/display/opengl_render_state.h>
#include <pangolin/gl/gldraw.h>
#include <pangolin/video/video_input.h>

#include <Eigen/Core>

#include "utils.h"
#include "constants.h"

using namespace std;

// TODO: refactor
// TODO: put some stuff in constants

inline void glDrawVertices(
        size_t num_vertices, const GLfloat *const vertex_ptr, GLenum mode,
        size_t elements_per_vertex = pangolin::GlFormatTraits<GLfloat>::components,
        size_t vertex_stride_bytes = 0) {
    if (num_vertices > 0) {
        PANGO_ENSURE(vertex_ptr != nullptr);
        PANGO_ENSURE(mode != GL_LINES || num_vertices % 2 == 0, "number of vertices (%) must be even in GL_LINES mode",
                     num_vertices);

        glVertexPointer(elements_per_vertex, pangolin::GlFormatTraits<GLfloat>::gltype, vertex_stride_bytes,
                        vertex_ptr);
        glEnableClientState(GL_VERTEX_ARRAY);
        glDrawArrays(mode, 0, num_vertices);
        glDisableClientState(GL_VERTEX_ARRAY);
    }
}

void goodGetFrustumVertices(GLfloat u0, GLfloat v0, GLfloat fu, GLfloat fv, int w, int h, GLfloat scale) {
    const GLfloat xl = scale * u0;
    const GLfloat xh = scale * (w * fu + u0);
    const GLfloat yl = scale * v0;
    const GLfloat yh = scale * (h * fv + v0);

    const GLfloat verts[] = {
            xl, yl, scale, xh, yl, scale,
            xh, yh, scale, xl, yh, scale,
            xl, yl, scale, 0, 0, 0,
            xh, yl, scale, 0, 0, 0,
            xl, yh, scale, 0, 0, 0,
            xh, yh, scale
    };

    glDrawVertices(11, verts, GL_LINE_STRIP, 3);
}
// TODO: optimize this

pair<vector<Eigen::Matrix<float, 4, 1>>, GLfloat *>
getFrustumVertices(GLfloat u0, GLfloat v0, GLfloat fu, GLfloat fv, int w, int h, GLfloat scale) {

    const GLfloat xl = scale * u0;
    const GLfloat xh = scale * (w * fu + u0);
    const GLfloat yl = scale * v0;
    const GLfloat yh = scale * (h * fv + v0);
    const int vertCount = 11;
    GLfloat verts[] = {
            xl, yl, scale, xh, yl, scale,
            xh, yh, scale, xl, yh, scale,
            xl, yl, scale, 0, 0, 0,
            xh, yl, scale, 0, 0, 0,
            xl, yh, scale, 0, 0, 0,
            xh, yh, scale
    };

    vector<Eigen::Matrix<float, 4, 1>> homogVerts;
    for (int i = 0; i < vertCount; i++) {
        homogVerts.push_back(
                (Eigen::Matrix<float, 4, 1>() << verts[3 * i], verts[3 * i + 1], verts[3 * i + 2], 1).finished());
    }
    return make_pair(homogVerts, verts);
//    glDrawVertices(vertCount, verts, GL_LINE_STRIP, 3);
}

int main(int /*argc*/, char ** /*argv*/ ) {
    cv::VideoCapture cap(constants::cameraId);
    if (!cap.isOpened()) {
        cout << "Broken Camera";
        return -1;
    }
    cap.set(cv::CAP_PROP_FPS, 60);
    cv::Size displaySize = cv::Size(constants::imgWidth, constants::imgHeight);
    cv::Ptr<cv::aruco::Dictionary> arucoDictionary = cv::aruco::Dictionary::get(cv::aruco::DICT_5X5_100);
    cv::Ptr<cv::aruco::DetectorParameters> parameters = cv::aruco::DetectorParameters::create();
    cv::FileStorage calibFile(constants::calibPath, cv::FileStorage::READ);
    cout << calibFile.isOpened() << endl;
    auto cameraMatrix = calibFile.operator[]("K").mat(); // I think incorrect
    auto distCoeffs = calibFile.operator[]("D").mat(); // I think incorrect

    cout << cameraMatrix << endl;
    calibFile.~FileStorage();

    vector<vector<cv::Point3f>> arucoPts; // convert to Point3f instead of vector for i j k
    vector<vector<cv::Point2f>> arucoPts2d;

    for (const auto &i: constants::rawArucoPts) {
        vector<cv::Point3f> tmp;
        vector<cv::Point2f> tmp2d;
        for (auto j: i) {
            tmp.push_back(cv::Point3f(j[0], j[1], j[2]));
            tmp2d.push_back(cv::Point2f(j[0], j[1]));
        }
        arucoPts.push_back(tmp);
        arucoPts2d.push_back(tmp2d);
    }

    cv::Ptr<cv::aruco::Board> board = cv::aruco::Board::create(arucoPts, arucoDictionary, constants::arucoIds);
    vector<vector<cv::Point2f>> detectedArucoCorners, rejectedArucoCorners;
    vector<int> detectedArucoIds;

    cv::Vec3d rvec, tvec;

    pangolin::CreateWindowAndBind("Main", int(640 * 1.5), int(480 * 1.5));
    glEnable(GL_DEPTH_TEST);

    // viewing state of virtual camera for rendering scene; intrinsics and extrinsics
    pangolin::OpenGlRenderState s_cam(
            pangolin::ProjectionMatrix(640, 480, 420, 420, 320, 240, 0.2, 100),
            pangolin::ModelViewLookAt(-2, 2, -2, 0, 0, 0, pangolin::AxisY)
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
            .SetBounds(2/3, 1.0f, 0, 1 / 3.0f, (float) constants::imgWidth / (float) constants::imgHeight)
            .SetLock(pangolin::LockLeft, pangolin::LockTop);
    cv::Mat frame, displayFrame, undistortedFrame;
    pangolin::GlTexture imageTexture(constants::imgWidth, constants::imgHeight, GL_RGB, false, 0, GL_RGB,
                                     GL_UNSIGNED_BYTE);
    while (!pangolin::ShouldQuit()) {
        // Clear screen and activate view to render into
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        d_cam.Activate(s_cam);

        cap >> frame;
//        cvtColor(frame, frame, cv::RGB2BGR);
        displayFrame = frame.clone();
        undistortedFrame = frame.clone();

        cv::aruco::detectMarkers(frame, arucoDictionary, detectedArucoCorners, detectedArucoIds, parameters,
                                 rejectedArucoCorners);
        cv::aruco::refineDetectedMarkers(frame, board, detectedArucoCorners, detectedArucoIds, rejectedArucoCorners,
                                         cameraMatrix, distCoeffs);
        for (auto corner: detectedArucoCorners) {
            for (auto pt: corner) {
                cv::circle(displayFrame, pt, 10, cv::Scalar(255, 255, 0), cv::FILLED);
            }
        }
        vector<pair<int, vector<cv::Point2f>>> tmp_corners;
        vector<cv::Point2f> tmp_corners_src, tmp_corners_dst;
        if (detectedArucoIds.size() == 4) {
            tmp_corners_src.clear();
            tmp_corners_dst.clear();
            cv::aruco::estimatePoseBoard(detectedArucoCorners, detectedArucoIds, board, cameraMatrix, distCoeffs, rvec,
                                         tvec);
            for (int i = 0; i < detectedArucoIds.size(); i++) {
                tmp_corners.push_back(make_pair(detectedArucoIds[i], detectedArucoCorners[i]));
            }
            sort(tmp_corners.begin(), tmp_corners.end(), Utils::pairSortComparator);

            for (auto i: tmp_corners) {
                for (auto c: i.second) {
                    tmp_corners_dst.push_back(c);
                }
            }
            // TODO: move this out
            for (auto i: arucoPts2d) {
                for (auto c: i) {
                    c.x = c.x * (float) constants::imgWidth / 20.7;
                    c.y = c.y * (float) constants::imgHeight / 19.7;
                    tmp_corners_src.push_back(c); // Multiplier to make bigger in final image
                }
            }

            tmp_corners.clear();
//            cout << " rvec: " << rvec << " tvec: " << tvec << endl;
            // TODO: use rodrigues on rvec and tvec to turn into projection matrix
        }
        try {
            /* Planar Rectification based on Aruco Markers */

            // Maps real world coords of board to those in the image
            //TODO: is it bad to create objects constantly in loop instead of initializing outside?
            cv::Mat H = cv::findHomography(tmp_corners_src, tmp_corners_dst, cv::RANSAC, 5);
            // Apply perspective transformation to original image
            cv::warpPerspective(displayFrame, undistortedFrame, H.inv(), displaySize, cv::INTER_LINEAR);
        }
        catch (...) {
            cout << "Not Yet Found" << endl;
        }


        // Render OpenGL Cube

        glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
        // TODO: this is working
        goodGetFrustumVertices(-0.5, -0.5, 1, 1, 1, 1, 0.25);
        // TODO: this is not working :(
        // TODO: rename vertices
        auto frustrum = getFrustumVertices(-0.5, -0.5, 1, 1, 1, 1, 0.25);
        vector<Eigen::Matrix<float, 4, 1>> frustumVertices = frustrum.first;
        for (auto v : frustumVertices) {
            cout << v << ", ";
        }
        cout << endl << endl << endl;
//        glDrawVertices(11, frustrum.second, GL_LINE_STRIP, 3);
//        Eigen::Matrix4f transformationMatrix;
//        transformationMatrix << 0, 0, 0, 0,
//                0, 0, 0, 0,
//                0, 0, 0, 0,
//                0, 0, 0, 0;
//
//        for (auto vertex: frustumVertices) {
//            vertex = transformationMatrix * vertex;
//        }

        cv::vconcat(displayFrame, undistortedFrame, displayFrame);
        cv::resize(displayFrame, displayFrame, displaySize);
        cv::flip(displayFrame, displayFrame, 0);
        // TODO: clean up how these images are stacked because very scuffed atm
        // TODO: Clean up dimensions between pangolin window, actual image, and display Image which is big time mess
        // TODO: no squish camera
        // TODO: plot tvec and rvec
        // TODO: point clouds
        // TODO: menu bar

//        cv::imshow("Window", displayFrame);
//        cv::waitKey(0);

        imageTexture.Upload(displayFrame.data, GL_BGR, GL_UNSIGNED_BYTE);
        d_image.Activate();
        glColor3f(1, 1, 1);
        imageTexture.RenderToViewport();

        // Swap frames and Process Events
        pangolin::FinishFrame();
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}
