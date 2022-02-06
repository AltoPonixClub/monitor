#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QWidget>

#include <QString>
#include <unordered_map>
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QGridLayout>

#include "viewBase.h"

class Chart {
public:
    Chart(QString name, std::pair<int, int> scale, int history);

    void addPoint(double value);
    QChartView *getChartView();

private:
    std::vector<std::pair<double, double>> mPoints;
    int mHistory;

    QChart *chart;
    QChartView *chartView;
    QLineSeries *series;
};

class LiveGraph : public ViewBase {
public:
    LiveGraph(QString name);
  QWidget *createView();

  void initChart(std::string key, QString name, std::pair<int, int> scale, int history);
  void updateChart(std::string key, double value);

private:
    std::unordered_map<std::string, Chart> charts;
    QGridLayout *layout;
    int row, col;
    int rowMax = 3;
};

#endif // CHARTVIEW_H
