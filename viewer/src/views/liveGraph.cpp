#include <string>
#include <QApplication>
#include <QChartView>
#include <QLineSeries>
#include <QtOpenGLWidgets/qopenglwidget.h>
#include <QtWidgets/qmainwindow.h>
#include <QGridLayout>
#include <QtCharts/QValueAxis>

#include "liveGraph.h"
#include "utils/utils.h"

LiveGraph::LiveGraph(QString name) {
    this->name = name;
    layout = new QGridLayout();
}

QWidget *LiveGraph::createView() {
    QWidget *widget = new QWidget();

    QPalette palette = widget->palette();
    palette.setColor(QPalette::Window, QRgb(qRgba(45,49,58,255)));

    initChart("test", "test", std::make_pair(10, 100), 5);
    updateChart("test", 1);
    updateChart("test", 2);
    updateChart("test", 5);
    updateChart("test", 20);
    updateChart("test", 50);

    initChart("abc", "abc", std::make_pair(10, 100), 5);
    updateChart("abc", 1);
    updateChart("abc", 2);
    updateChart("abc", 5);
    updateChart("abc", 20);
    updateChart("abc", 50);

    initChart("qwe", "qwe", std::make_pair(10, 100), 5);
    updateChart("qwe", 1);
    updateChart("qwe", 2);
    updateChart("qwe", 5);
    updateChart("qwe", 20);
    updateChart("qwe", 50);

    initChart("awerbc", "awerbc", std::make_pair(10, 100), 5);
    updateChart("awerbc", 1);
    updateChart("awerbc", 2);
    updateChart("awerbc", 5);
    updateChart("awerbc", 20);
    updateChart("awerbc", 50);

    initChart("alkjbc", "alkjbc", std::make_pair(10, 100), 5);
    updateChart("alkjbc", 1);
    updateChart("alkjbc", 2);
    updateChart("alkjbc", 5);
    updateChart("alkjbc", 20);
    updateChart("alkjbc", 50);

    initChart("lkj", "lkj", std::make_pair(10, 100), 5);
    updateChart("lkj", 1);
    updateChart("lkj", 2);
    updateChart("lkj", 5);
    updateChart("lkj", 20);
    updateChart("lkj", 50);

    initChart("jhg", "jhg", std::make_pair(10, 100), 5);
    updateChart("jhg", 1);
    updateChart("jhg", 2);
    updateChart("jhg", 5);
    updateChart("jhg", 20);
    updateChart("jhg", 50);

    widget->setLayout(layout);
    return widget;
}

void LiveGraph::initChart(std::string key, QString name, std::pair<int, int> scale, int history) {
    Chart chart = {new QChartView(), new QChart(), new QLineSeries(),
                   0, history,
                   new QValueAxis, new QValueAxis};

    chart.mChart->setTitle(name);
    chart.mChart->legend()->hide();
    chart.mChart->createDefaultAxes();

    QFont labelsFont;
    labelsFont.setPixelSize(12);
    chart.axisX->setLabelsFont(labelsFont);
    chart.axisY->setLabelsFont(labelsFont);

    QBrush axisBrush(Qt::white);
    chart.axisX->setLabelsBrush(axisBrush);
    chart.axisY->setLabelsBrush(axisBrush);

    QFont font;
    font.setPixelSize(15);
    chart.mChart->setTitleFont(font);
    chart.mChart->setTitleBrush(QBrush(Qt::white));

    QPen seriesPen(QRgb(qRgba(0, 154, 141, 255)));
    seriesPen.setWidth(2);
    chart.mSeries->setPen(seriesPen);

    chart.mChart->setPlotAreaBackgroundBrush(QColor(33,37,46));
    chart.mChart->setPlotAreaBackgroundVisible(true);
    chart.mChart->setBackgroundBrush(QColor(45,49,58));

    chart.axisX->setRange(0, scale.first);
    chart.axisY->setRange(0, scale.second);
    chart.mChart->addAxis(chart.axisX, Qt::AlignBottom);
    chart.mChart->addAxis(chart.axisY, Qt::AlignLeft);
    chart.mSeries->attachAxis(chart.axisX);
    chart.mSeries->attachAxis(chart.axisY);

    chart.mChart->addSeries(chart.mSeries);
    chart.mChartView->setChart(chart.mChart);
    chart.mChartView->setRenderHint(QPainter::Antialiasing);

    charts[key] = chart;
    layout->addWidget(charts[key].mChartView, col, row);
    if (++row > rowMax) {
        row = 0;
        col++;
    }
}

void LiveGraph::updateChart(std::string key, double value) {
    charts[key].mSeries->append(charts[key].mNumPoints++, value); //change from numpoints to time
    if (charts[key].mNumPoints > charts[key].mHistory) {
        charts[key].mChart->scroll(charts[key].mNumPoints, 0);
    }
    charts[key].mChart->removeSeries(charts[key].mSeries);
    charts[key].mChart->addSeries(charts[key].mSeries);
    charts[key].mSeries->attachAxis(charts[key].axisX);
    charts[key].mSeries->attachAxis(charts[key].axisY);
}
