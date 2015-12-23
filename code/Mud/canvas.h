#ifndef CANVAS_H
#define CANVAS_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QGestureEvent>

#include "grid.h"

class Canvas : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    Canvas(QWidget *parent = 0);
    ~Canvas();

    // TODO: Const?
    void build(Grid *grid);

protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;

    bool event(QEvent *event) Q_DECL_OVERRIDE;

private:
    QOpenGLShaderProgram *shaderProgram;
    void initializeShaders();

    QOpenGLBuffer *particlesBufferObject;
    QOpenGLVertexArrayObject gridArrayObject;
    void initializeBuffers();
    void updateBuffers(QVector<QVector3D> locations);

    QMatrix4x4 mvpMatrix;
    float zoomingFactor;
    float rotationAngle;

    void setUniformValues();
    void drawParticles();
    bool isAllocated(QOpenGLBuffer *buffer);

    bool gestureEvent(QGestureEvent *event);
    void pinchTriggered(QPinchGesture *gesture);
};

#endif // CANVAS_H
