#ifndef CANVAS_H
#define CANVAS_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>

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
    void initializeGL();
    void paintGL();

private:
    QOpenGLShaderProgram *shaderProgram;
    void initializeShaders();

    QOpenGLBuffer *particlesBufferObject;
    QOpenGLVertexArrayObject gridArrayObject;
    void initializeBuffers();
    void updateBuffers(QVector<QVector3D> locations);

    void drawParticles();
    bool isAllocated(QOpenGLBuffer *buffer);
};

#endif // CANVAS_H
