#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>
#include <pangolin/display/display.h>
#include <pangolin/display/view.h>
#include <pangolin/handler/handler.h>
#include <pangolin/gl/gldraw.h>
#include "utils.h"

using namespace std;

int main( int /*argc*/, char** /*argv*/ ) {
    cv::VideoCapture cap(-1);
    if (!cap.isOpened()) {
        cout << "Broken Camera";
        return -1;
    }
    cv::Size img_size = cv::Size(320, 240);
    cv::Size display_size = cv::Size(2*320, 2*240);
    cap.set(cv::CAP_PROP_FPS, 60);
    cv::Ptr<cv::aruco::Dictionary> arucoDictionary = cv::aruco::Dictionary::get(cv::aruco::DICT_5X5_100);
    cv::Ptr<cv::aruco::DetectorParameters> parameters = cv::aruco::DetectorParameters::create();
    cv::FileStorage calibFile("/home/aoberai/programming/altoponix/monitor/unit/outputs.yml", cv::FileStorage::READ);
    cout << calibFile.isOpened() << endl;
    auto cameraMatrix = calibFile.operator[]("K").mat(); // I think incorrect
    auto distCoeffs = calibFile.operator[]("D").mat(); // I think incorrect

    cout << cameraMatrix << endl;
    calibFile.~FileStorage();

    vector<vector<vector<float>>> rawArucoPts = {{{0, 0, 0}, {0, 4.6, 0}, {4.6, 4.6, 0}, {4.6, 0, 0}},
                                       {{16.1, 0, 0}, {16.1, 4.6, 0}, {20.7, 4.6, 0}, {20.7, 0, 0}},
                                       {{0, 15.1, 0}, {0, 19.7, 0}, {4.6, 19.7, 0}, {4.6, 15.1, 0}},
                                       {{16.1, 15.1, 0}, {16.1, 19.7, 0}, {20.7, 19.7, 0}, {20.7, 15.1, 0}}};

    vector<cv::Point2f> target = {cv::Point2f(0, 0), cv::Point2f(19.8, 0), cv::Point2f(19.8, 20.8), cv::Point2f(0, 20.8)};

    vector<vector<cv::Point3f>> arucoPts; // convert to Point3f instead of vector for i j k
    vector<vector<cv::Point2f>> arucoPts2d;

    for (const auto& i : rawArucoPts) {
        vector<cv::Point3f> tmp;
        vector<cv::Point2f> tmp2d;
        for (auto j : i) {
            tmp.push_back(cv::Point3f(j[0], j[1], j[2]));
            tmp2d.push_back(cv::Point2f(j[0], j[1]));
        }
        arucoPts.push_back(tmp);
        arucoPts2d.push_back(tmp2d);
    }

    vector<int> arucoIds = {24, 42, 69, 48};

    cv::Ptr<cv::aruco::Board> board = cv::aruco::Board::create(arucoPts, arucoDictionary, arucoIds);
    vector<vector<cv::Point2f>> detectedArucoCorners, rejectedArucoCorners;
    vector<int> detectedArucoIds;

    cv::Vec3d rvec, tvec;

    pangolin::CreateWindowAndBind("Main",640*1.5,480*1.5);
    glEnable(GL_DEPTH_TEST);

    // Define Projection and initial ModelView matrix
    pangolin::OpenGlRenderState s_cam(
            pangolin::ProjectionMatrix(640,480,420,420,320,240,0.2,100),
            pangolin::ModelViewLookAt(-2,2,-2, 0,0,0, pangolin::AxisY)
    );

    // Create Interactive View in window
    pangolin::Handler3D handler(s_cam);
    pangolin::View& d_cam = pangolin::CreateDisplay()
            .SetBounds(0.0, 1.0, 0.0, 1.0, -640.0f/480.0f)
            .SetHandler(&handler);

    cv::Mat frame, displayFrame, undistortedFrame;
    while (!pangolin::ShouldQuit()) {
        // Clear screen and activate view to render into
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        d_cam.Activate(s_cam);

        cap >> frame;
        displayFrame = frame.clone();
        undistortedFrame = frame.clone();

        cv::aruco::detectMarkers(frame, arucoDictionary, detectedArucoCorners, detectedArucoIds, parameters, rejectedArucoCorners);
        cv::aruco::refineDetectedMarkers(frame, board, detectedArucoCorners, detectedArucoIds, rejectedArucoCorners, cameraMatrix, distCoeffs);
        for (auto corner : detectedArucoCorners)  {
            for (auto pt : corner) {
                cv::circle(frame, pt, 10, cv::Scalar(255, 255, 0), cv::FILLED);
            }
        }
        vector<pair<int, vector<cv::Point2f>>> tmp_corners;
        vector<cv::Point2f> tmp_corners_src, tmp_corners_dst;
        if (detectedArucoIds.size() == 4) {
            cv::aruco::estimatePoseBoard(detectedArucoCorners, detectedArucoIds, board, cameraMatrix, distCoeffs, rvec, tvec);
            for (int i = 0; i < detectedArucoIds.size(); i++) {
                tmp_corners.push_back(make_pair(detectedArucoIds[i], detectedArucoCorners[i]));
            }
            sort(tmp_corners.begin(), tmp_corners.end(), Utils::pairSortComparator);

            for (auto i : tmp_corners) {
                for (auto c : i.second) {
                    tmp_corners_dst.push_back(c);
                }
            }
            for (auto i : arucoPts2d) {
                for (auto c : i) {
                    tmp_corners_src.push_back(c*15); // Multiplier to make bigger in final image
                }
            }

            /**
             * Initiating Planar Rectification based on Aruco Markers
             */
            // Maps real world coords of board to those in the image
            //TODO: is it bad to create objects constantly in loop instead of initializing outside?
            cv::Mat H = cv::findHomography(tmp_corners_src, tmp_corners_dst, cv::RANSAC, 5);
            // Apply perspective transformation to original image
            cv::warpPerspective(frame, undistortedFrame, H.inv(), display_size, cv::INTER_LINEAR);

            tmp_corners.clear();
            tmp_corners_src.clear();
            tmp_corners_dst.clear();
//            cout << " rvec: " << rvec << " tvec: " << tvec << endl;
            // TODO: use rodrigues on rvec and tvec to turn into projection matrix
        }

        cv::resize(displayFrame, displayFrame, display_size);

        // TODO: Display image on pangolin window
//        cv::imshow("Raw", displayFrame);
        cv::imshow("Undistorted", undistortedFrame);
        if ((char) cv::waitKey(1) == 27)
            break;

        // Render OpenGL Cube
        pangolin::glDrawColouredCube();
        // Swap frames and Process Events
        pangolin::FinishFrame();
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}
