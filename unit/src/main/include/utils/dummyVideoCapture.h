#ifndef MONITOR_DUMMYVIDEOCAPTURE_H
#define MONITOR_DUMMYVIDEOCAPTURE_H

#include <opencv2/videoio.hpp>

class DummyVideoCapture : public cv::VideoCapture {
  private:
    cv::Mat img;

  public:
    DummyVideoCapture();
    DummyVideoCapture(std::string filename);
    DummyVideoCapture &operator>>(cv::Mat &image) override;
};

#endif // MONITOR_DUMMYVIDEOCAPTURE_H
