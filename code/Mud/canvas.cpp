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
    initializeOpenGLFunctions();

    glClearColor(0.9f, 0.9f, 0.9f, 1.0f);

    initializeShaders();
    initializeBuffers();
}

void Canvas::initializeShaders()
{
    this->shaderProgram = new QOpenGLShaderProgram();
    this->shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, "shaders/mudvert.glsl");
    this->shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, "shaders/mudfrag.glsl");
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

    this->shaderProgram->bind();
    this->gridArrayObject.bind();

    glPointSize(3.0f);
    glDrawArrays(GL_POINTS, 0, 3);

    this->gridArrayObject.release();
    this->shaderProgram->release();
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
