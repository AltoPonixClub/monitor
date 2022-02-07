#ifndef QT_TCPTHREAD_H
#define QT_TCPTHREAD_H

#include <QThread>

class TCPThread : public QThread {
  Q_OBJECT

  void run();

signals:
  void dataReceived(std::string info);
};

#endif // QT_TCPTHREAD_H
