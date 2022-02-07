#include <QString>
#include <iostream>
#include <utils/TCPThread.h>
#include <utils/zmq.h>

void TCPThread::run() {

  std::cout << "Starting receiver" << std::endl;

  zmq::context_t context(1);
  zmq::socket_t subscriber(context, ZMQ_SUB);
  subscriber.connect("tcp://localhost:5555");
  subscriber.setsockopt(ZMQ_SUBSCRIBE, "", 0);

  while (true) {
    zmq::message_t msg;
    subscriber.recv(&msg);
    std::string msg_str =
        std::string(static_cast<char *>(msg.data()), msg.size());
    emit dataReceived(msg_str);
  }
}