
#include <subsystems/vision.h>
#include <config/constants.h>
#include <utils/utils.h>
#include "../archived/cv/constants.h"

Vision::Vision() {
    cap = cv::VideoCapture(constants::vision::kCameraId);
    if (!cap.isOpened()) {
        std::cout << "Vision Hardware Broken" << std::endl;
        return;
    }
    cap.set(cv::CAP_PROP_FPS, constants::vision::kFps);
    std::cout << "Vision Hardware Initialized";
    calibFile = cv::FileStorage(constants::vision::kCalibPath, cv::FileStorage::READ);
    assert(calibFile.isOpened());
    cameraMatrix = calibFile.operator[]("K").mat(); // extrinsics
    distCoeffs = calibFile.operator[]("D").mat(); // intrinsics
    calibFile.~FileStorage();
    for (const auto &i: constants::vision::kBoardArucoPts) {
        for (auto c: i) {
            transform_src.emplace_back(
                    c.x * constants::vision::kImgSize.width / constants::physical::kPlatformDim.width,
                    c.y * constants::vision::kImgSize.height /
                    constants::physical::kPlatformDim.height); // Multiplier to make bigger in final image
        }
    }

}

void Vision::read(State *state) {
    cv::Mat frame;
    cap >> frame;
    cv::resize(frame, frame, constants::vision::kImgSize);
    state->capFrame = frame;

    cv::aruco::detectMarkers(frame, constants::vision::kArucoDictionary, state->detectedArucoCorners,
                             state->detectedArucoIds, constants::vision::kArucoParams,
                             state->rejectedArucoCorners);
    cv::aruco::refineDetectedMarkers(frame, constants::vision::kBoard, state->detectedArucoCorners,
                                     state->detectedArucoIds,
                                     state->rejectedArucoCorners,
                                     cameraMatrix, distCoeffs);

    state->transform_dst.clear();
    if (state->detectedArucoIds.size() == 4) {
        std::vector<std::pair<int, std::vector<cv::Point2f>>> tmp_corners;
        cv::aruco::estimatePoseBoard(state->detectedArucoCorners, state->detectedArucoIds, constants::vision::kBoard,
                                     cameraMatrix,
                                     distCoeffs, state->cam_rvec,
                                     state->cam_tvec);
        // Sets up transform dst for findHomography
        for (int i = 0; i < state->detectedArucoIds.size(); i++)
            tmp_corners.emplace_back(state->detectedArucoIds[i], state->detectedArucoCorners[i]);
        sort(tmp_corners.begin(), tmp_corners.end(), Utils::pairSortComparator);
        for (const auto &corner: tmp_corners) {
            for (auto pt: corner.second)
                state->transform_dst.push_back(pt);
        }
        try {
            /* Planar Rectification based on Aruco Markers */

            // Maps real world coords of board to those in the image
            cv::Mat H = cv::findHomography(transform_src, state->transform_dst, cv::RANSAC, 5);
            // Apply perspective transformation to original image
            cv::warpPerspective(state->capFrame, state->undistortedFrame, H.inv(), constants::display::kImgDispSize,
                                cv::INTER_LINEAR);
            state->undistortedFrame = state->undistortedFrame(
                    cv::Rect(0, 0, constants::vision::kImgSize.width, constants::vision::kImgSize.height));
        }
        catch (...) {
            std::cout << "Not Yet Found Board" << std::endl;
        }
        // TODO: use rodrigues on rvec and tvec to turn into projection matrix
    }
}

void Vision::calculate(State *state, Commands *commands, Outputs *outputs) {
    outputs->editedCapFrame = state->capFrame.clone();
    for (const auto &corner: state->detectedArucoCorners) {
        for (auto pt: corner) {
            cv::circle(outputs->editedCapFrame, pt, constants::display::kArucoCircRadius, constants::display::kAqua,
                       cv::FILLED);
        }
    }
}

void Vision::write(Outputs *outputs) {
}

Vision *Vision::instance() {
    if (Vision::pInstance == nullptr) {
        Vision::pInstance = new Vision();
    }
    return Vision::pInstance;
}

std::string Vision::name() {
    return std::string("vision");
}

