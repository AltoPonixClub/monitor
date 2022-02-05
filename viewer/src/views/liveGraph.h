#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QWidget>

#include <QString>

#include "viewBase.h"

class LiveGraph : public ViewBase {
public:
  LiveGraph(QString name);

  QWidget *createView();

private:
};

#endif // CHARTVIEW_H
