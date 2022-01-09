#include <subsystems/vision.h>
#include <config/configs.h>
#include <utils/utils.h>
#include <spdlog/spdlog.h>

// TODO: specify read only write only based on annotations
Vision::Vision(State *state, Commands *commands, Outputs *outputs) {
    // Opens number of cameras based on wanted monocular, stereo, or none
    switch (commands->visionWantedState) {
        case Commands::VisionState::OFF:
            break;
        case Commands::VisionState::STEREO:
            this->rightCap = cv::VideoCapture(Configs::Vision::kRightCamId);
            this->rightCap.set(cv::CAP_PROP_FPS, Configs::Vision::kFps);
            assert(this->rightCap.isOpened());
        case Commands::VisionState::MONOCULAR: // TODO: how to enforce this because you dont actually need VisionState
            this->leftCap = cv::VideoCapture(Configs::Vision::kLeftCamId);
            this->leftCap.set(cv::CAP_PROP_FPS, Configs::Vision::kFps);
            assert(this->leftCap.isOpened());
            break;
    }
    spdlog::info("Vision: Successful Initialization");

    // Load Single Cam Calibration (move this to Configs)
    calibFile = cv::FileStorage(Configs::Vision::kCalibPath, cv::FileStorage::READ);
    assert(calibFile.isOpened());
    cameraMatrix = calibFile.operator[]("K").mat(); // extrinsics
    distCoeffs = calibFile.operator[]("D").mat(); // intrinsics
    calibFile.~FileStorage();

    // TODO:  Mark constexpr to precalculate these value things ?? how this work
    for (const auto &i: Configs::Vision::kBoardArucoPts) {
        for (auto c: i) {
            transform_src.emplace_back(
                    c.x * Configs::Vision::kImgSize.width / Configs::Physical::kPlatformDim.width,
                    c.y * Configs::Vision::kImgSize.height /
                    Configs::Physical::kPlatformDim.height); // Multiplier to make bigger in final image
        }
    }

    state->capFrame = state->undistortedFrame = cv::Mat(Configs::Vision::kImgSize.height,
                                                        Configs::Vision::kImgSize.width, CV_8UC3,
                                                        Configs::Display::kGrey);
    state->camRotMat = cv::Mat(3, 3, CV_8UC1);
    state->camRvec, state->camTvec = cv::Vec3d(0, 0, 0);
    state->depthMap = std::vector<std::vector<float>>(Configs::Vision::kImgSize.height,
                                                      std::vector<float>(Configs::Vision::kImgSize.width, 0));
}

void Vision::read(State *state) {
    cv::Mat frame;
    leftCap >> frame;
    cv::resize(frame, frame, Configs::Vision::kImgSize);
    state->capFrame = frame;

    cv::aruco::detectMarkers(frame, Configs::Vision::kArucoDictionary, state->detectedArucoCorners,
                             state->detectedArucoIds, Configs::Vision::kArucoParams,
                             state->rejectedArucoCorners);
    cv::aruco::refineDetectedMarkers(frame, Configs::Vision::kBoard, state->detectedArucoCorners,
                                     state->detectedArucoIds,
                                     state->rejectedArucoCorners,
                                     cameraMatrix, distCoeffs);

    state->transform_dst.clear();
    if (state->detectedArucoIds.size() > 1) {
        std::vector<std::pair<int, std::vector<cv::Point2f>>> tmp_corners;
        cv::aruco::estimatePoseBoard(state->detectedArucoCorners, state->detectedArucoIds, Configs::Vision::kBoard,
                                     cameraMatrix,
                                     distCoeffs, state->camRvec,
                                     state->camTvec);
        cv::Rodrigues(state->camRvec, state->camRotMat);
        state->camRotMat = state->camRotMat; // TODO: figure out inverse or not
        spdlog::info("Vision: Rvec: {}, Tvec: {} {} {}", *state->camRvec.val, state->camTvec.val[0],
                     state->camTvec.val[1], state->camTvec.val[2]);
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
            cv::warpPerspective(state->capFrame, state->undistortedFrame, H.inv(), Configs::Display::kImgDispSize,
                                cv::INTER_LINEAR);
            state->undistortedFrame = state->undistortedFrame(
                    cv::Rect(0, 0, Configs::Vision::kImgSize.width, Configs::Vision::kImgSize.height));
        }
        catch (...) {
            spdlog::error("Vision: Could not find homography");
        }
        // TODO: use rodrigues on rvec and tvec to turn into projection matrix
    }
    // TODO: stereo pointcloud
    for (int i = 0; i < state->depthMap.size(); i++) {
        for (int j = 0; j < state->depthMap[0].size(); j++) {
            state->depthMap[i][j] = sin(i / 10 + 100 * (state->timeS - state->initTimeS)) -
                                    cos(j / 10 - 100 * (state->timeS - state->initTimeS)) / 3 + 3;
        }
    }
}

void Vision::calculate(State *state, Commands *commands, Outputs *outputs) {
    outputs->editedCapFrame = state->capFrame.clone();
    for (const auto &corner: state->detectedArucoCorners) {
        for (auto pt: corner) {
            cv::circle(outputs->editedCapFrame, pt, Configs::Display::kArucoCircRadius, Configs::Display::kAqua,
                       cv::FILLED);
        }
    }
}

void Vision::write(Outputs *outputs) {
}

Vision *Vision::instance(State *state, Commands *commands, Outputs *outputs) {
    if (Vision::pInstance == nullptr) {
        Vision::pInstance = new Vision(state, commands, outputs);
    }
    return Vision::pInstance;
}

std::string Vision::name() {
    return std::string("vision");
}

