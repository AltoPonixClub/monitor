//
// Created by aoberai on 12/20/21.
//

#ifndef MONITOR_UTILS_H
#define MONITOR_UTILS_H

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <Eigen/Core>
#include <pangolin/display/display.h>
#include <pangolin/display/view.h>
#include <pangolin/handler/handler.h>
#include <pangolin/gl/gl.h>
#include <pangolin/gl/glinclude.h>
#include <pangolin/gl/glformattraits.h>
#include <pangolin/display/opengl_render_state.h>
#include <pangolin/gl/gldraw.h>
#include <pangolin/video/video_input.h>

class Utils {
public:
    template<typename T>
    static std::string vec2str(std::vector<T> array);
    static bool pairSortComparator(std::pair<int, std::vector<cv::Point2f>> a, std::pair<int, std::vector<cv::Point2f>> b);
    static std::vector<Eigen::Matrix<float, 4, 1>> getFrustumVertices(float u0, float v0, float fu, float fv, int w, int h, float scale);
    static void drawFrustum(std::vector<Eigen::Matrix<float, 4, 1>> vertices);

};


#endif //MONITOR_UTILS_H
