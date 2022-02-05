#include <string>
#include <QApplication>
#include <QChartView>
#include <QLineSeries>
#include <QPushButton>
#include <QtOpenGLWidgets/qopenglwidget.h>
#include <QtWidgets/qmainwindow.h>

#include "liveGraph.h"

LiveGraph::LiveGraph(QString name) { this->name = name; }

QWidget *LiveGraph::createView() {
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