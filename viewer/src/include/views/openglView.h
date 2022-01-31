#ifndef OPENGLVIEW_H
#define OPENGLVIEW_H

#include "util/geometryengine.h"
#include "views/viewBase.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QString>

class GeometryEngine;

class OpenGLView : public QOpenGLWidget, protected QOpenGLFunctions, public ViewBase
{
Q_OBJECT

public:
    using QOpenGLWidget::QOpenGLWidget;
    ~OpenGLView();

    OpenGLView(QString name);

    QWidget *createView();

protected:
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void timerEvent(QTimerEvent *e) override;

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void initShaders();
    void initTextures();

private:

    QBasicTimer timer;
    QOpenGLShaderProgram program;
    GeometryEngine *geometries = nullptr;

    QOpenGLTexture *texture = nullptr;

    QMatrix4x4 projection;

    QVector2D mousePressPosition;
    QVector3D rotationAxis;
    qreal angularSpeed = 0;
    QQuaternion rotation;

};

#endif // OPENGLVIEW_H
