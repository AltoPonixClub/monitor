#include <QMouseEvent>
#include <iostream>
#include "openglView.h"

using namespace std::chrono;

OpenGLView::OpenGLView(QString name) {
    this->name = name;
    kLookAt = QVector3D(0, 0, 0);
    kUpAxis = QVector3D(0, 1, 0);
    posX = posY = 0;
    rad = 7;
    keys = std::unordered_set<int>();
}

OpenGLView::~OpenGLView() {
    makeCurrent();
    delete texture;
    delete geometries;
    doneCurrent();
}

QWidget *OpenGLView::createView() { return this; }

void OpenGLView::mousePressEvent(QMouseEvent *e) {
}

void OpenGLView::keyPressEvent(QKeyEvent *event) {
    keys.emplace(event->key());
}

void OpenGLView::keyReleaseEvent(QKeyEvent *event) {
    keys.erase(event->key());
}

void OpenGLView::mouseReleaseEvent(QMouseEvent *e) {
}

void OpenGLView::timerEvent(QTimerEvent *) {
    update();
}

void OpenGLView::initializeGL() {
    initializeOpenGLFunctions();

    initShaders();
//    initTextures();
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
    const qreal zNear = 0.5, zFar = 30.0, fov = 45.0;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
}

void OpenGLView::paintGL() {
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//    glClearColor(0.5, 0.7, 0.7, 0.0f); // Background Color
//    texture->bind();

    // Calculate model view transformation; https://learnopengl.com/Getting-started/Camera
    QMatrix4x4 matrix;

    for (auto i : keys) {
        if (i == Qt::Key_W) {
            std::cout << "w" << std::endl;
            posY += 0.07;
        }
        if (i == Qt::Key_A) {
            std::cout << "a" << std::endl;
            posX -= 0.07;
        }
        if (i == Qt::Key_S) {
            std::cout << "s" << std::endl;
            posY -= 0.07;
        }
        if (i == Qt::Key_D) {
            std::cout << "d" << std::endl;
            posX += 0.07;
        }
    }

    matrix.lookAt(QVector3D(posX, posY, getCamZ(posX, posY)), kLookAt, kUpAxis);

    // Set modelview-projection matrix
    program.setUniformValue("mvp_matrix", projection * matrix);

    // Use texture unit 0 which contains cube.png
//    program.setUniformValue("texture", 0);

    glClearColor(0.5, 0.5, 0.5, 0);
    // Draw cube geometry
    geometries->drawCubeGeometry(&program);

    glClearColor(0.5, 0.7, 0.7, 0.0f); // Background Color
}

float OpenGLView::getCamZ(float posX, float posY) {
    return sqrt(- posX * posX - posY * posY + rad * rad);
}
