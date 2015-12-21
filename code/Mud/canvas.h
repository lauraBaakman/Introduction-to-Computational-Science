#ifndef CANVAS_H
#define CANVAS_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class Canvas : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    Canvas(QWidget *parent = 0);
    ~Canvas();

protected:
    void initializeGL();
    void paintGL();

private:
    void initializeShaders();
    void initializeBuffers();
};

#endif // CANVAS_H
