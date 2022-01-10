#ifndef MONITOR_UTILS_H
#define MONITOR_UTILS_H

#include <Eigen/Core>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <pangolin/display/display.h>
#include <pangolin/display/view.h>
#include <pangolin/gl/gl.h>
#include <pangolin/gl/gldraw.h>
#include <pangolin/gl/glformattraits.h>
#include <pangolin/gl/glinclude.h>
#include <pangolin/handler/handler.h>
#include <pangolin/video/video_input.h>
#include <vector>

class Utils {
  public:
    //    static float inline kPi = 3.1415;

    template <typename T> static std::string vec2str(std::vector<T> array);

    static std::string matEig2str(Eigen::MatrixXd mat);

    static float deg2rad(float num);

    static bool pairSortComparator(std::pair<int, std::vector<cv::Point2f>> a,
                                   std::pair<int, std::vector<cv::Point2f>> b);

    static std::vector<Eigen::Matrix<float, 4, 1>>

    getFrustumVertices(float u0, float v0, float fu, float fv, int w, int h,
                       float scale);

    static long getUnixTimestamp();

};

#endif // MONITOR_UTILS_H