#ifndef MONITOR_CONFIGS_H
#define MONITOR_CONFIGS_H

#include <opencv2/aruco.hpp>
#include <opencv2/aruco/dictionary.hpp>
#include <opencv2/opencv.hpp>

// TODO: define in a source file?
// TODO: doesnt follow clang style guide

class Configs {
  public:
    static void configure();

    class Physical {
      public:
        static inline const cv::Size kPlatformDim = cv::Size(20.7, 19.7);
    };
    class Vision {
      public:
        static inline const int kLeftCamId = 0, kRightCamId = 1, kFps = 60;
        static inline const cv::Size kImgSize = cv::Size(int(640), int(480));
        static inline const std::string kCalibPath = std::string(
            "/home/aoberai/programming/altoponix/monitor/unit/outputs.yml");
        static inline const std::vector<std::vector<cv::Point3f>>
            kBoardArucoPts = {
                {cv::Point3f(0, 0, 0), cv::Point3f(0, 4.6, 0),
                 cv::Point3f(4.6, 4.6, 0), cv::Point3f(4.6, 0, 0)},

                {cv::Point3f(16.1, 0, 0), cv::Point3f(16.1, 4.6, 0),
                 cv::Point3f(20.7, 4.6, 0), cv::Point3f(20.7, 0, 0)},

                {cv::Point3f(0, 15.1, 0), cv::Point3f(0, 19.7, 0),
                 cv::Point3f(4.6, 19.7, 0), cv::Point3f(4.6, 15.1, 0)},

                {cv::Point3f(16.1, 15.1, 0), cv::Point3f(16.1, 19.7, 0),
                 cv::Point3f(20.7, 19.7, 0), cv::Point3f(20.7, 15.1, 0)}};
        static inline const cv::Ptr<cv::aruco::Dictionary> kArucoDictionary =
            cv::aruco::Dictionary::get(cv::aruco::DICT_5X5_100);
        static inline const cv::Ptr<cv::aruco::DetectorParameters>
            kArucoParams = cv::aruco::DetectorParameters::create();
        static inline const std::vector<int> kArucoIds = {24, 42, 48, 69};
        static inline const cv::Ptr<cv::aruco::Board> kBoard =
            cv::aruco::Board::create(kBoardArucoPts, kArucoDictionary,
                                     kArucoIds);
    };
    class Display {
      public:
        static inline const cv::Size kDispSize =
            cv::Size(int(640 * 2), int(480 * 2));
        static inline const cv::Size kImgDispSize =
            cv::Size(int(640), int(2 * 480));
        static inline const float kMeshDensity = 250.0; // must be float
        static inline const int kArucoCircRadius = 7;
        static inline const cv::Scalar kAqua{255, 255, 0};   // BGR
        static inline const cv::Scalar kGrey{100, 100, 100}; // BGR
        static inline const cv::Scalar kBlack{0, 0, 0};      // BGR
    };
    class Uploader {
      public:
        static inline const std::string kMonitorId =
            "672ef79b4d0a4805bc529d1ae44bc26b";
        static inline const std::string kUploadUrl =
            "http://altoponix-database.herokuapp.com/api/v1/monitors/update";
        static inline const std::string kMeasurementNames[8] = {
            "atmospheric_temp",        "reservoir_temp",
            "light_intensity",         "soil_moisture",
            "electrical_conductivity", "ph",
            "dissolved_oxygen",        "air_flow"};
    };
};

#endif // MONITOR_CONFIGS_H
