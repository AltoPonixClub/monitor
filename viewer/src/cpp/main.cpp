#include "views/chartView.h"
#include "views/viewBase.h"
#include "views/openglView.h"

#include <QApplication>
#include <QPushButton>
#include <QtWidgets/qmainwindow.h>
#include <QChartView>
#include <QLineSeries>
#include <QtOpenGLWidgets/qopenglwidget.h>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QMainWindow window;
    QTabWidget *tabWidget = new QTabWidget();

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    std::vector<ViewBase *> views{
            new ChartView("Chart"),
            new OpenGLView("OpenGL"),
    };

    for (ViewBase *view : views) {
        tabWidget->addTab(view->createView(), view->name);
    }

    window.setCentralWidget(tabWidget);
    window.resize(900, 900);
    window.show();
    return QApplication::exec();
}
