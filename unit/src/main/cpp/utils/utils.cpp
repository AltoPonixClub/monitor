#include <string>
#include <utils/utils.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <QCoreApplication>
#include <QtSerialPort/QSerialPort>
#include <QSerialPortInfo>
#include <unistd.h>

template<typename T>
std::string Utils::vec2str(std::vector<T> arr) {
    std::string ot = std::string("[");
    for (auto v: arr) {
        ot += (std::to_string(v) + std::string(", "));
    }
    ot += std::string("]");
    return ot;
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

void Utils::drawFrustum(std::vector<Eigen::Matrix<float, 4, 1>> vertices) {
    for (int i = 0; i < vertices.size(); i++) {
        for (int j = i; j < vertices.size(); j++) {
            pangolin::glDrawLine(vertices[i].data()[0], vertices[i].data()[1], vertices[i].data()[2],
                                 vertices[j].data()[0], vertices[j].data()[1], vertices[j].data()[2]);
        }
    }
}

template std::string Utils::vec2str<int>(std::vector<int>);

template std::string Utils::vec2str<float>(std::vector<float>);

void Utils::daq(std::string request) {

    //QCoreApplication app(argc, argv); this is needed somewhere or it kind of works but throws an error

    QSerialPort serial;
    serial.setPortName("cu.usbmodem113301");    //changes
    serial.open(QIODevice::ReadWrite);
    serial.setBaudRate(QSerialPort::Baud9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::HardwareControl);

    QByteArray output(request.c_str(), request.length());
    QByteArray input;

    if (serial.isOpen() && serial.isWritable()) {
        sleep(3);   //dependent on system (import and stuff may be different on Windows)
        serial.write(output);
        serial.waitForBytesWritten();
        if (serial.waitForReadyRead()) {
            while (serial.waitForReadyRead(10))
                input += serial.readAll();
        }
        serial.close();
    }
    return input.toStdString();
}

