
#include "config/configs.h"

void Configs::configure() {
    cv::FileStorage calibFile;
    calibFile =
            cv::FileStorage(Configs::Vision::kStereoCalibPath, cv::FileStorage::READ);
    assert(calibFile.isOpened());

    Vision::StereoCalib::K1 = calibFile.operator[]("K1").mat();
    Vision::StereoCalib::D1 = calibFile.operator[]("D1").mat();
    Vision::StereoCalib::K2 = calibFile.operator[]("K2").mat();
    Vision::StereoCalib::D2 = calibFile.operator[]("D2").mat();
    Vision::StereoCalib::R = calibFile.operator[]("R").mat();
    Vision::StereoCalib::T = calibFile.operator[]("T").mat();
    Vision::StereoCalib::E = calibFile.operator[]("E").mat();
    Vision::StereoCalib::F = calibFile.operator[]("F").mat();
    Vision::StereoCalib::R1 = calibFile.operator[]("R1").mat();
    Vision::StereoCalib::R2 = calibFile.operator[]("R2").mat();
    Vision::StereoCalib::P1 = calibFile.operator[]("P1").mat();
    Vision::StereoCalib::P2 = calibFile.operator[]("P2").mat();
    Vision::StereoCalib::Q = calibFile.operator[]("Q").mat();

    calibFile.~FileStorage();
}
