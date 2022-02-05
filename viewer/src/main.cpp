#include "views/liveGraph.h"
#include "views/pointCloud.h"
#include "views/viewBase.h"

#include <QApplication>
#include <QChartView>
#include <QLineSeries>
#include <QPushButton>
#include <QtOpenGLWidgets/qopenglwidget.h>
#include <QtWidgets/qmainwindow.h>
#include <QStyleFactory>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  QApplication::setStyle(QStyleFactory::create("Fusion"));
  QPalette p;
  p = qApp->palette();
  p.setColor(QPalette::Window, QColor(53,53,53));
  p.setColor(QPalette::Button, QColor(53,53,53));
  p.setColor(QPalette::Highlight, QColor(142,45,197));
  p.setColor(QPalette::ButtonText, QColor(255,255,255));
  p.setColor(QPalette::Text, QColor(255,255,255));
  qApp->setPalette(p);
  QMainWindow window;
  QTabWidget *tabWidget = new QTabWidget();

  QSurfaceFormat format;
  format.setDepthBufferSize(24);
  QSurfaceFormat::setDefaultFormat(format);

  std::unordered_map<std::string, ViewBase*> views {
      std::make_pair("live_graph", new LiveGraph("Live Graph")),
      std::make_pair("point_cloud", new PointCloud("Point Cloud"))
  };

  for (auto i : views) {
    tabWidget->addTab(i.second->createView(), i.second->name);
  }

  views["point_cloud"]->createView()->setFocusPolicy(Qt::ClickFocus);

  window.setCentralWidget(tabWidget);
  window.resize(900, 900);
  window.show();
  return QApplication::exec();
}
