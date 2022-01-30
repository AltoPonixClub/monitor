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
        static inline const int kLeftCamId = -1, kRightCamId = 1,
                                kFps = 60; // switch index
        static inline const cv::Size kImgSize = cv::Size(int(640), int(480));
        static inline const std::string kLeftCalibPath = std::string(
            "/home/aoberai/programming/altoponix/monitor/unit/left_cam.yml");
        static inline const std::string kRightCalibPath = std::string(
            "/home/aoberai/programming/altoponix/monitor/unit/right_cam.yml");
        static inline const std::string kStereoCalibPath = std::string(
            "/home/aoberai/programming/altoponix/monitor/unit/stereo_cam.yml");
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
        class StereoCalib {
          public:
            static inline cv::Mat K1 = cv::Mat();
            static inline cv::Mat D1 = cv::Mat();
            static inline cv::Mat K2 = cv::Mat();
            static inline cv::Mat D2 = cv::Mat();
            static inline cv::Mat R = cv::Mat();
            static inline cv::Mat T = cv::Mat();
            static inline cv::Mat E = cv::Mat();
            static inline cv::Mat F = cv::Mat();
            static inline cv::Mat R1 = cv::Mat();
            static inline cv::Mat R2 = cv::Mat();
            static inline cv::Mat P1 = cv::Mat();
            static inline cv::Mat P2 = cv::Mat();
            static inline cv::Mat Q = cv::Mat();
        };
        static inline float kStereoWlsLambda = 12000;
        static inline float kStereoWlsSigma = 2.5;
        static inline std::string kLeftDummyImgPath =
            std::string("/home/aoberai/programming/altoponix/monitor/unit/"
                        "assets/rectified_1.png");
        static inline std::string kRightDummyImgPath =
            std::string("/home/aoberai/programming/altoponix/monitor/unit/"
                        "assets/rectified_2.png");
    };

    class Display {
      public:
        static inline const cv::Size kDispSize =
            cv::Size(int(640 * 2), int(480 * 2));
        static inline const cv::Size kImgDispSize =
            cv::Size(int(640), int(2 * 480));
        static inline const float kMeshDensity = 150.0; // must be float
        static inline const int kArucoCircRadius = 7;
        static inline const cv::Scalar kAqua{255, 255, 0};   // BGR
        static inline const cv::Scalar kGrey{100, 100, 100}; // BGR
        static inline const cv::Scalar kBlack{0, 0, 0};      // BGR
        static inline const std::string kWindowName = "Main";
    };

    class DAQ {
      public:
        static inline const std::string kArduinoPort = "cu.usbmodem13401";
    };

    class Uploader {
      public:
        static inline const std::string kMonitorId =
            "672ef79b4d0a4805bc529d1ae44bc26b";
        static inline const std::string kEndpoint =
            "https://altoponix-database.herokuapp.com/api/v1";
        static inline const std::string kUploadMethod = "/monitors/update";
        static inline const std::string kLoginMethod = "/login/monitor";
        static inline const std::string kMeasurementNames[8] = {
            "atmospheric_temp",        "reservoir_temp",
            "light_intensity",         "soil_moisture",
            "electrical_conductivity", "ph",
            "dissolved_oxygen",        "air_flow"};
    };
};

#endif // MONITOR_CONFIGS_H
