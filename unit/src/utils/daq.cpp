#include "daq.h"
#include <QCoreApplication>
#include <QSerialPortInfo>
#include <QtSerialPort/QSerialPort>
#include <iostream>
#include <spdlog/spdlog.h>

DAQ::DAQ(std::string port) {
    serial.setPortName(QString::fromStdString(port));
    serial.open(QIODevice::ReadWrite);
    serial.setBaudRate(QSerialPort::Baud9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::HardwareControl);
}

std::string DAQ::request(std::string request) {

    QByteArray output(request.c_str(), request.length());
    QByteArray input;

    if (serial.isOpen() && serial.isWritable()) {
        serial.write(output);
        serial.waitForBytesWritten();
        if (serial.waitForReadyRead()) {
            while (serial.waitForReadyRead(10))
                input += serial.readAll();
        }
        //        serial.close();
    } else {
        spdlog::info("Invalid Serial Port");
    }
    return input.toStdString();
}

void DAQ::availablePorts() {
    // print available ports (could put port in config or something)
    foreach (const QSerialPortInfo &serialPortInfo,
             QSerialPortInfo::availablePorts()) {
        std::cout << serialPortInfo.portName().toStdString();
    }
}

DAQ *DAQ::instance(std::string port) {
    if (DAQ::pInstance == nullptr) {
        DAQ::pInstance = new DAQ(port);
    }
    return DAQ::pInstance;
}
