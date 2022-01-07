#include <string>
#include <chrono>
#include <utils/utils.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

template<typename T>
std::string Utils::vec2str(std::vector<T> arr) {
    std::string ot = std::string("[");
    for (auto v: arr) {
        ot += (std::to_string(v) + std::string(", "));
    }
    ot += std::string("]");
    return ot;
}

// TODO: not sure this works
std::string matEig2str(Eigen::MatrixXd mat) {
    std::stringstream ss;
    ss << mat;
    return ss.str();
}

bool Utils::pairSortComparator(std::pair<int, std::vector<cv::Point2f>> a, std::pair<int, std::vector<cv::Point2f>> b) {
    return (a.first < b.first);
}

std::vector<Eigen::Matrix<float, 4, 1>>
Utils::getFrustumVertices(float u0, float v0, float fu, float fv, int w, int h, float scale) {
    const float xl = scale * u0;
    const float xh = scale * (w * fu + u0);
    const float yl = scale * v0;
    const float yh = scale * (h * fv + v0);

    std::vector<Eigen::Matrix<float, 4, 1>> homogVerts;
    homogVerts.push_back((Eigen::Matrix<float, 4, 1>() << xl, yl, scale, 1).finished());
    homogVerts.push_back((Eigen::Matrix<float, 4, 1>() << xh, yh, scale, 1).finished());
    homogVerts.push_back((Eigen::Matrix<float, 4, 1>() << xl, yh, scale, 1).finished());
    homogVerts.push_back((Eigen::Matrix<float, 4, 1>() << xh, yl, scale, 1).finished());
    homogVerts.push_back((Eigen::Matrix<float, 4, 1>() << 0, 0, 0, 1).finished());
    return homogVerts;
}


float Utils::deg2rad(float num) {
    return num * 3.1415 / 180;
}

long Utils::getUnixTimestamp() {
    return std::chrono::system_clock::now().time_since_epoch() /
           std::chrono::milliseconds(1);
}

void Utils::configureLogger() {
    auto logger = spdlog::stdout_color_mt("console");
    spdlog::set_default_logger(logger);
}

template std::string Utils::vec2str<int>(std::vector<int>);

template std::string Utils::vec2str<float>(std::vector<float>);