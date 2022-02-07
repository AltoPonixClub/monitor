#include <iostream>
#include <utils/TCPThread.h>
#include <utils/TabWidget.h>

void TabWidget::startTCPThread() {
  TCPThread *workerThread = new TCPThread;
  connect(workerThread, SIGNAL(dataReceived(std::string)),
          SLOT(onDataReceived(std::string)));
  connect(workerThread, SIGNAL(finished()), workerThread, SLOT(deleteLater()));
  workerThread->start();
}

void TabWidget::onDataReceived(std::string data) {
  std::cout << "[TabWidget]: Received data: " << data << std::endl;
}