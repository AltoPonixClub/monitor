#include "views/chartView.h"
#include <QMouseEvent>

#include <string>

#include <QApplication>
#include <QPushButton>
#include <QtWidgets/qmainwindow.h>
#include <QChartView>
#include <QLineSeries>
#include <QtOpenGLWidgets/qopenglwidget.h>

ChartView::ChartView(QString name) {
    this->name = name;
}

QWidget *ChartView::createView() {
    QChartView *chartView = new QChartView();
    QChart *chart = new QChart();
    QLineSeries *series = new QLineSeries();

    series->append(0, 5);
    series->append(1, 10);
    series->append(2, 30);

    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Line Chart");

    chartView->setChart(chart);

    return chartView;
}