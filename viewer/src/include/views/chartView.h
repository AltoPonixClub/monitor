#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QWidget>

#include <QString>

#include "viewBase.h"

class ChartView : public ViewBase
{
public:

    ChartView(QString name);

    QWidget *createView();

private:

};

#endif // CHARTVIEW_H
