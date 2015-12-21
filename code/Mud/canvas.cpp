#include "canvas.h"
#include <QDebug>

Canvas::Canvas(QWidget *parent) :
    QOpenGLWidget(parent)
{
    qDebug() << "Constructor Canvas";
}

Canvas::~Canvas()
{
    qDebug() << "Destructor Canvas";
}

void Canvas::initializeGL()
{
    qDebug() << "InitializeGL not implemented yet.";
}

void Canvas::initializeShaders()
{
    qDebug() << "initializeShaders not implemented yet.";
}

void Canvas::initializeBuffers()
{
    qDebug() << "initializeBuffers not implemented yet.";
}

void Canvas::paintGL()
{
    qDebug() << "paintGL not implemented yet.";
}
