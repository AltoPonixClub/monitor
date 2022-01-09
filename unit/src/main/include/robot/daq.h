#ifndef MONITOR_DAQ_H
#define MONITOR_DAQ_H

#include <iostream>
#include "config/constants.h"
#include <QtSerialPort/QSerialPort>

class DAQ{
public:
    DAQ(std::string port);

    std::string request(std::string request);

    static void availablePorts();

    static DAQ *instance(std::string port);

private:
    static inline DAQ *pInstance = nullptr;
};

#endif //MONITOR_DAQ_H
