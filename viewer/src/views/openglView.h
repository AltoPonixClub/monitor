#ifndef OPENGLVIEW_H
#define OPENGLVIEW_H

#include <QBasicTimer>
#include <QMatrix4x4>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLWidget>
#include <QQuaternion>
#include <QString>
#include <QVector2D>
#include "viewBase.h"
#include "../util/geometryEngine.h"

class OpenGLView : public QOpenGLWidget,
                   protected QOpenGLFunctions,
                   public ViewBase {
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
  //    void keyReleaseEvent(QKeyEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;

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

  double posX, posY, posZ;

  double getCamZ(double posX, double posY);
};

#endif // OPENGLVIEW_H
