#ifndef QT_CAMSTREAMS_H
#define QT_CAMSTREAMS_H

#include "viewBase.h"

class CamStreams : public ViewBase {
  CamStreams(QString name);

  QWidget *createView();
};

#endif // QT_CAMSTREAMS_H
