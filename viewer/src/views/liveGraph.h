#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QWidget>

#include <QString>
#include <unordered_map>
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QGridLayout>
#include <QValueAxis>

#include "viewBase.h"

class LiveGraph : public ViewBase {
public:
    LiveGraph(QString name);
  QWidget *createView();

  void initChart(std::string key, QString name, std::pair<int, int> scale, int history);
  void updateChart(std::string key, double value);

private:
    class Chart {
    public:
        QChartView *mChartView;
        QChart *mChart;
        QLineSeries *mSeries;
        int mNumPoints;
        int mHistory;
        QValueAxis *axisX;
        QValueAxis *axisY;
    };
    std::unordered_map<std::string, Chart> charts;
    QGridLayout *layout;
    int row, col;
    int rowMax = 2; //starts at 0
};

#endif // CHARTVIEW_H
