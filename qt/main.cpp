#include <QApplication>
#include <QPushButton>
#include <QtWidgets/qmainwindow.h>
#include <QChartView>
#include <QLineSeries>

QChartView *createChartView() {
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

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QMainWindow window;
    QTabWidget *tabWidget = new QTabWidget();

    tabWidget->addTab(createChartView(), "Charts");
    window.setCentralWidget(tabWidget);
    window.resize(900, 900);
    window.show();
    return QApplication::exec();
}
