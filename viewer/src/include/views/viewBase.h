#ifndef VIEWBASE_H
#define VIEWBASE_H

#include <QWidget>
#include <QString>

class ViewBase
{
public:
    virtual QWidget *createView() = 0;

    QString name;
};

#endif // VIEWBASE_H
