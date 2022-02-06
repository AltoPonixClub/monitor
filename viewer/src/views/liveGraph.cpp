#include <string>
#include <QApplication>
#include <QChartView>
#include <QLineSeries>
#include <QtOpenGLWidgets/qopenglwidget.h>
#include <QtWidgets/qmainwindow.h>
#include <QGridLayout>

#include "liveGraph.h"
#include "utils/utils.h"

LiveGraph::LiveGraph(QString name) { this->name = name; }

QWidget *LiveGraph::createView() {
  QWidget *widget = new QWidget();

  for (std::pair<const std::string, Chart> chart : charts) {
      layout->addWidget(chart.second.getChartView(), row, col);
      if (++row > rowMax) {
          row = 0;
          col++;
      }
  }
  widget->setLayout(layout);
  return widget;
}

void LiveGraph::initChart(std::string key, QString name, std::pair<int, int> scale, int history) {
    charts[key] = Chart(name, scale, history);
    layout->addWidget(charts[key].getChartView(), row, col);
    if (++row > rowMax) {
        row = 0;
        col++;
    }
}

void LiveGraph::updateChart(std::string key, double value) {
    charts[key].addPoint(value);
}

Chart::Chart(QString name, std::pair<int, int> scale, int history) {
    chartView = new QChartView();
    chart = new QChart();
    chart->setTitle(name);
    mHistory = history; //TODO: add history via circular buffer or find Qt way
    chart->legend()->hide();
    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setRange(0, scale.first);
    chart->axes(Qt::Vertical).first()->setRange(0, scale.second);

    series = new QLineSeries();
    for (std::pair<int, int> point : mPoints) {
        series->append(point.first, point.second);
    }
    chart->addSeries(series);

    chartView->setChart(chart);
}

void Chart::addPoint(double value) {
    mPoints.emplace_back(Utils::getTimeMs(), value);
    series->append(Utils::getTimeMs(), value);
}

QChartView *Chart::getChartView() {
    return chartView;
}
