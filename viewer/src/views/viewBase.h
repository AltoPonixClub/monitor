#ifndef VIEWBASE_H
#define VIEWBASE_H

#include <QString>
#include <QWidget>

class ViewBase {
public:
  virtual QWidget *createView() = 0;

  QString name;
};

#endif // VIEWBASE_H
