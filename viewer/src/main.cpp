#include "views/chartView.h"
#include "views/openglView.h"
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
  tabWidget->setFocusPolicy(Qt::WheelFocus);

  QSurfaceFormat format;
  format.setDepthBufferSize(24);
  QSurfaceFormat::setDefaultFormat(format);

  std::vector<ViewBase *> views{
      new ChartView("Live Charts"),
      new OpenGLView("3d Mesh")
  };

  for (ViewBase *view : views) {
    tabWidget->addTab(view->createView(), view->name);
  }

  window.setCentralWidget(tabWidget);
  window.resize(900, 900);
  window.show();
  return QApplication::exec();
}
