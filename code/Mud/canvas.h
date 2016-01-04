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
    // Shaders
    QOpenGLShaderProgram *shaderProgram;
    void initializeShaders();

    // Buffers
    QOpenGLBuffer *particlesBufferObject;
    QOpenGLBuffer *springIndicesBufferObject;
    QOpenGLVertexArrayObject gridArrayObject;
    void initializeBuffers();
    void updateBuffers(QVector<QVector3D> locations);

    // Transformations
    QMatrix4x4 mvpMatrix;
    float zoomingFactor;
    float rotationAngle;

    // Helpers
    void setUniformValues();
    void constructModelViewProjectionMatrix();
    bool isAllocated(QOpenGLBuffer *buffer);
    void reset();

    // Helpers for build
    QVector<int> buildFreeParticleIndices(QVector<Particle*> freeParticles);
    QVector<int> buildFixedParticleIndices(QVector<Particle*> fixedParticles);
    QVector<int> buildSpringIndices(QVector<Spring> springs);

    // Draw
    void drawParticles();
    void drawSprings();

    // Events
    bool gestureEvent(QGestureEvent *event);
    void pinchTriggered(QPinchGesture *gesture);
};

#endif // CANVAS_H
