#ifndef QT_TABWIDGET_H
#define QT_TABWIDGET_H

#include <QTabWidget>

class TabWidget : public QTabWidget {
  Q_OBJECT

public:
  void startTCPThread();

public slots:
  void onDataReceived(std::string data);
};

#endif // QT_TABWIDGET_H
