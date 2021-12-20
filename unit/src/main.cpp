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
    int cap_dim[2] = {320, 240};
    cap.set(cv::CAP_PROP_FPS, 60);
//    cap.set(cv::CAP_PROP_FRAME_WIDTH, cap_dim[0]);
//    cap.set(cv::CAP_PROP_FRAME_HEIGHT, cap_dim[1]);
    cv::Ptr<cv::aruco::Dictionary> arucoDictionary = cv::aruco::Dictionary::get(cv::aruco::DICT_5X5_100);
    cv::Ptr<cv::aruco::DetectorParameters> parameters = cv::aruco::DetectorParameters::create(); cv::FileStorage calibFile("outputs.yml", cv::FileStorage::READ);
    auto cameraMatrix = calibFile.operator[]("K"); // I think incorrect
    auto distMatrix = calibFile.operator[]("D"); // I think incorrect
    calibFile.~FileStorage();

    vector<vector<vector<float>>> rawArucoPts = {{{0, 0, 0}, {0, 4.6, 0}, {4.6, 4.6, 0}, {4.6, 0, 0}},
                                       {{16.1, 0, 0}, {16.1, 4.6, 0}, {20.7, 4.6, 0}, {20.7, 0, 0}},
                                       {{0, 15.1, 0}, {0, 19.7, 0}, {4.6, 19.7, 0}, {4.6, 15.1, 0}},
                                       {{16.1, 15.1, 0}, {16.1, 19.7, 0}, {20.7, 19.7, 0}, {20.7, 15.1, 0}}};
    vector<vector<cv::Point3f>> arucoPts; // convert to Point3f instead of vector for i j k
    for (const auto& i : rawArucoPts) {
        vector<cv::Point3f> tmp;
        for (auto j : i) {
             tmp.push_back(cv::Point3f(j[0], j[1], j[2]));
        }
        arucoPts.push_back(tmp);
    }

    vector<int> arucoIds = {24, 42, 69, 48};

    cv::Ptr<cv::aruco::Board> board = cv::aruco::Board::create(arucoPts, arucoDictionary, arucoIds);
    vector<vector<cv::Point2f>> detectedArucoCorners;
    vector<int> detectedArucoIds;

    // rvecs, tvecs = None, None

    cv::Mat frame;
    cv::Mat displayFrame;
    while (true) {
        cap >> frame;
        displayFrame = frame.clone();

        cv::aruco::detectMarkers(frame, arucoDictionary, detectedArucoCorners, detectedArucoIds, parameters);
        if (detectedArucoIds.size() == 4) {
            cv::aruco::estimatePoseBoard(detectedArucoCorners, detectedArucoIds, board, cameraMatrix, ...)
        }


        if (!detectedArucoIds.empty()) {
            cout << Utils::vec2str(detectedArucoIds) << endl;
        }
        cv::aruco::drawDetectedMarkers(displayFrame, detectedArucoCorners, detectedArucoIds);
        cv::resize(displayFrame, displayFrame, cv::Size(cap_dim[0] * 2, cap_dim[1] * 2));
        cv::imshow("Window", displayFrame);
        if ((char) cv::waitKey(1) == 27)
            break;
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}
