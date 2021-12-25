
#include <subsystems/vision.h>
#include <config/constants.h>
#include <utils/utils.h>

// TODO should these vars be put in configure func or outside - probably outside?
// TODO: better error logging
Vision::Vision() {
    cap = cv::VideoCapture(constants::vision::cameraId);
    if (!cap.isOpened()) {
        std::cout << "Vision Hardware Broken" << std::endl;
        return;
    }
    cap.set(cv::CAP_PROP_FPS, constants::vision::fps);
    std::cout << "Vision Hardware Initialized";
    arucoDictionary = cv::aruco::Dictionary::get(cv::aruco::DICT_5X5_100);
    arucoParams = cv::aruco::DetectorParameters::create();
    calibFile = cv::FileStorage(constants::vision::calibPath, cv::FileStorage::READ);
    std::cout << calibFile.isOpened() << std::endl;
    cameraMatrix = calibFile.operator[]("K").mat(); // extrinsics
    distCoeffs = calibFile.operator[]("D").mat(); // intrinsics
    calibFile.~FileStorage();
    board = cv::aruco::Board::create(constants::vision::boardArucoPts, arucoDictionary, constants::vision::arucoIds);
    for (const auto &i: constants::vision::boardArucoPts) {
        for (auto c: i) {
            transform_src.push_back(
                    cv::Point2f(c.x * constants::vision::imgSize.width / constants::vision::platformDim.width,
                                c.y * constants::vision::imgSize.height /
                                constants::vision::platformDim.height)); // Multiplier to make bigger in final image
        }
    }

}

void Vision::read(State *state) {
    cv::Mat frame;
    cap >> frame;
    cv::resize(frame, frame, constants::vision::imgSize);
    state->capFrame = frame;

    cv::aruco::detectMarkers(frame, arucoDictionary, state->detectedArucoCorners, state->detectedArucoIds, arucoParams,
                             state->rejectedArucoCorners);
    cv::aruco::refineDetectedMarkers(frame, board, state->detectedArucoCorners, state->detectedArucoIds,
                                     state->rejectedArucoCorners,
                                     cameraMatrix, distCoeffs);

    state->transform_dst.clear();
    if (state->detectedArucoIds.size() == 4) {
        std::vector<std::pair<int, std::vector<cv::Point2f>>> tmp_corners;
        cv::aruco::estimatePoseBoard(state->detectedArucoCorners, state->detectedArucoIds, board, cameraMatrix,
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
            cv::warpPerspective(state->capFrame, state->undistortedFrame, H.inv(), constants::display::imgDispSize,
                                cv::INTER_LINEAR);
            state->undistortedFrame = state->undistortedFrame(
                    cv::Rect(0, 0, constants::vision::imgSize.width, constants::vision::imgSize.height));
        }
        catch (...) {
            std::cout << "Not Yet Found Board" << std::endl;
        }
        // TODO: use rodrigues on rvec and tvec to turn into projection matrix
//        cout << "translation: " << tvec << endl;
    }
}

void Vision::write(Outputs *outputs) {
}

void Vision::calculate(State *state, Commands *commands, Outputs *outputs) {
    // TODO: put corners on img
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

