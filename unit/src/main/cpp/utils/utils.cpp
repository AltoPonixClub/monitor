#include <string>
#include <utils/utils.h>

template <typename T> std::string Utils::vec2str(std::vector<T> arr) {
    std::string ot = std::string("[");
    for (auto v : arr) {
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

bool Utils::pairSortComparator(std::pair<int, std::vector<cv::Point2f>> a,
                               std::pair<int, std::vector<cv::Point2f>> b) {
    return (a.first < b.first);
}

std::vector<Eigen::Matrix<float, 4, 1>>
Utils::getFrustumVertices(float u0, float v0, float fu, float fv, int w, int h,
                          float scale) {
    const float xl = scale * u0;
    const float xh = scale * (w * fu + u0);
    const float yl = scale * v0;
    const float yh = scale * (h * fv + v0);

    std::vector<Eigen::Matrix<float, 4, 1>> homogVerts;
    homogVerts.push_back(
        (Eigen::Matrix<float, 4, 1>() << xl, yl, scale, 1).finished());
    homogVerts.push_back(
        (Eigen::Matrix<float, 4, 1>() << xh, yh, scale, 1).finished());
    homogVerts.push_back(
        (Eigen::Matrix<float, 4, 1>() << xl, yh, scale, 1).finished());
    homogVerts.push_back(
        (Eigen::Matrix<float, 4, 1>() << xh, yl, scale, 1).finished());
    homogVerts.push_back(
        (Eigen::Matrix<float, 4, 1>() << 0, 0, 0, 1).finished());
    return homogVerts;
}

float Utils::deg2rad(float num) { return num * 3.1415 / 180; }

template std::string Utils::vec2str<int>(std::vector<int>);

template std::string Utils::vec2str<float>(std::vector<float>);
