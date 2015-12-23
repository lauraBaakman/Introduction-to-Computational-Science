#include "canvas.h"
#include <QDebug>

#include <QWheelEvent>

Canvas::Canvas(QWidget *parent) :
    QOpenGLWidget(parent)
{
    qDebug() << "Constructor Canvas";

    this->zoomFactor = 1.0;
    this->mvpMatrix.setToIdentity();
}

Canvas::~Canvas()
{
    qDebug() << "Destructor Canvas";

    delete this->shaderProgram;
    delete this->particlesBufferObject;

    this->gridArrayObject.destroy();
}

void Canvas::initializeGL()
{
    qDebug() << "InitializeGL not implemented yet.";
    initializeOpenGLFunctions();

    glEnable(GL_DEPTH_TEST);
    // glEnable(GL_CULL_FACE);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    initializeShaders();
    initializeBuffers();
}

void Canvas::initializeShaders()
{
    this->shaderProgram = new QOpenGLShaderProgram();
    this->shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/mudvert.glsl");
    this->shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/mudfrag.glsl");
    this->shaderProgram->link();
}

void Canvas::initializeBuffers()
{
    this->gridArrayObject.create();
    this->gridArrayObject.bind();

    this->particlesBufferObject = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    this->particlesBufferObject->create();
    this->particlesBufferObject->bind();

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    this->gridArrayObject.release();
}

void Canvas::updateBuffers(QVector<QVector3D> locations)
{
    this->particlesBufferObject->bind();
    this->particlesBufferObject->allocate(locations.data(), locations.size() * sizeof(locations[0]));
    this->particlesBufferObject->release();
}

void Canvas::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (isAllocated(this->particlesBufferObject)) {
        this->shaderProgram->bind();
        setUniformValues();
        drawParticles();
        this->shaderProgram->release();
    }
}

void Canvas::setUniformValues()
{
    // Todo: Move
    mvpMatrix.setToIdentity();
//    mvpMatrix.rotate(0.0, 0.0, 0.0);
//    mvpMatrix.scale(1.0);
//    mvpMatrix.translate(0.0, 0.0, 0.0);
    mvpMatrix.scale(this->zoomFactor);

    this->shaderProgram->setUniformValue("mvpMatrix", mvpMatrix);
}

bool Canvas::isAllocated(QOpenGLBuffer *buffer)
{
    return buffer->size() != 0;
}

void Canvas::drawParticles()
{
    this->gridArrayObject.bind();

    glPointSize(10.0f);
    glDrawArrays(GL_POINTS, 0, 3);

    this->gridArrayObject.release();
}

void Canvas::zoom(float factor)
{
    this->zoomFactor = this->zoomFactor * factor;
    update();
}

void Canvas::build(Grid *grid)
{
    qDebug() << "Building buffers from grid...";
    QVector<QVector3D> locations;
    for(const Particle &particle : grid->getParticles())
    {
        locations.append(*(particle.getLocation()));
    }
    updateBuffers(locations);
    qDebug() << "Building buffers complete....";
}

void Canvas::wheelEvent(QWheelEvent *event)
{
    QPoint delta = event->pixelDelta();

    if(delta.y() > 0) {
        zoom(1.1);
    } else {
        zoom(0.9);
    }

    qDebug() << "Wheee ....";
}
