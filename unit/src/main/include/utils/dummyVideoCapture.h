#ifndef MONITOR_DUMMYVIDEOCAPTURE_H
#define MONITOR_DUMMYVIDEOCAPTURE_H

#include <opencv2/videoio.hpp>

class DummyVideoCapture: public cv::VideoCapture {
private:
    cv::Mat img;
public:
    DummyVideoCapture();
    DummyVideoCapture(std::string filename);
    //    bool open(const cv::String &filename, int apiPreference = cv::CAP_ANY) override;
    DummyVideoCapture& operator >> (CV_OUT cv::Mat& image) override;
};

#endif //MONITOR_DUMMYVIDEOCAPTURE_H
