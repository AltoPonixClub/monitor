#include <QMouseEvent>
#include <iostream>
#include "openglView.h"

OpenGLView::~OpenGLView() {
  makeCurrent();
  delete texture;
  delete geometries;
  doneCurrent();
}

OpenGLView::OpenGLView(QString name) { this->name = name; }

QWidget *OpenGLView::createView() { return this; }

void OpenGLView::mousePressEvent(QMouseEvent *e) {
  mousePressPosition = QVector2D(e->position());
}

void OpenGLView::keyPressEvent(QKeyEvent *event) {
  switch (event->key()) {
  case Qt::Key_W:
    std::cout << "w" << std::endl;
    posY += 0.1;
    break;
  case Qt::Key_A:
    std::cout << "a" << std::endl;
    posX -= 0.1;
    break;
  case Qt::Key_S:
    std::cout << "s" << std::endl;
    posY -= 0.1;
    break;
  case Qt::Key_D:
    std::cout << "d" << std::endl;
    posX += 0.1;
    break;
  }
  std::cout << "Cam Pose: " << getCamZ(posX, posY) << std::endl;
}

void OpenGLView::mouseReleaseEvent(QMouseEvent *e) {
  QVector2D diff = QVector2D(e->position()) - mousePressPosition;
  QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();
  qreal acc = diff.length() / 100.0;

  rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

  angularSpeed += acc;
}

void OpenGLView::timerEvent(QTimerEvent *) {
  angularSpeed *= 0.99;

  if (angularSpeed < 0.01) {
    angularSpeed = 0.0;
  } else {
    rotation =
        QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;

    update();
  }
}

void OpenGLView::initializeGL() {
  initializeOpenGLFunctions();

  glClearColor(0, 0, 0, 1);

  initShaders();
  initTextures();

  // Enable depth buffer
  glEnable(GL_DEPTH_TEST);

  // Enable back face culling
  glEnable(GL_CULL_FACE);

  geometries = new GeometryEngine;

  // Use QBasicTimer because its faster than QTimer
  timer.start(12, this);
}

void OpenGLView::initShaders() {
  // Compile vertex shader
  if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/noop.vert"))
    close();

  // Compile fragment shader
  if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/noop.frag"))
    close();

  // Link shader pipeline
  if (!program.link())
    close();

  // Bind shader pipeline for use
  if (!program.bind())
    close();
}

void OpenGLView::initTextures() {
  // Load cube.png image
  texture = new QOpenGLTexture(QImage(":/cube.png").mirrored());

  // Set nearest filtering mode for texture minification
  texture->setMinificationFilter(QOpenGLTexture::Nearest);

  // Set bilinear filtering mode for texture magnification
  texture->setMagnificationFilter(QOpenGLTexture::Linear);

  // Wrap texture coordinates by repeating
  // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
  texture->setWrapMode(QOpenGLTexture::Repeat);
}

void OpenGLView::resizeGL(int w, int h) {
  // Calculate aspect ratio
  qreal aspect = qreal(w) / qreal(h ? h : 1);

  // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
  const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;

  // Reset projection
  projection.setToIdentity();

  // Set perspective projection
  projection.perspective(fov, aspect, zNear, zFar);
}

void OpenGLView::paintGL() {
  // Clear color and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  texture->bind();

  // Calculate model view transformation
  QMatrix4x4 matrix;
  matrix.translate(0.0, 0.0, -5.0);
  matrix.rotate(rotation);

  // Set modelview-projection matrix
  program.setUniformValue("mvp_matrix", projection * matrix);

  // Use texture unit 0 which contains cube.png
  program.setUniformValue("texture", 0);

  // Draw cube geometry
  geometries->drawCubeGeometry(&program);
}

double OpenGLView::getCamZ(double posX, double posY) {
  return -sqrt(posX * posX + posY * posY - 1);
}
