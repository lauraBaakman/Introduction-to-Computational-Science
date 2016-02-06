#include "canvas.h"
#include <QDebug>

#include <QWheelEvent>

Canvas::Canvas(QWidget *parent) :
    QOpenGLWidget(parent)
{
    qDebug() << "Constructor Canvas";

    reset();

    // Register all gesture events.
    grabGesture(Qt::PinchGesture);
}

Canvas::~Canvas()
{
    qDebug() << "Destructor Canvas";

    delete this->shaderProgram;
    delete this->locationBufferObject;
    delete this->freeParticleIndicesBufferObject;
    delete this->fixedParticleIndicesBufferObject;
    delete this->springIndicesBufferObject;

    this->gridArrayObject.destroy();
}

void Canvas::initializeGL()
{
    initializeOpenGLFunctions();

    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

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

    this->locationBufferObject = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    this->locationBufferObject->setUsagePattern(QOpenGLBuffer::DynamicDraw);
    this->locationBufferObject->create();
    this->locationBufferObject->bind();

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    this->gridArrayObject.release();

    // Not bound to the VAO...
    this->freeParticleIndicesBufferObject = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    this->freeParticleIndicesBufferObject->setUsagePattern(QOpenGLBuffer::DynamicDraw);
    this->freeParticleIndicesBufferObject->create();

    this->fixedParticleIndicesBufferObject = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    this->fixedParticleIndicesBufferObject->setUsagePattern(QOpenGLBuffer::DynamicDraw);
    this->fixedParticleIndicesBufferObject->create();

    this->springIndicesBufferObject = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    this->springIndicesBufferObject->setUsagePattern(QOpenGLBuffer::DynamicDraw);
    this->springIndicesBufferObject->create();
}

void Canvas::updateLocationBuffer(QVector<QVector3D> locations)
{

    this->locationBufferObject->bind();
    this->locationBufferObject->allocate(locations.data(), locations.size() * sizeof(locations[0]));
    this->locationBufferObject->release();
}

void Canvas::updateFreeParticleBuffer(QVector<int> indices)
{
    this->freeParticleIndicesBufferObject->bind();
    this->freeParticleIndicesBufferObject->allocate(indices.data(), indices.size() * sizeof(indices[0]));
    this->freeParticleIndicesBufferObject->release();
}

void Canvas::updateFixedParticleBuffer(QVector<int> indices)
{
    this->fixedParticleIndicesBufferObject->bind();
    this->fixedParticleIndicesBufferObject->allocate(indices.data(), indices.size() * sizeof(indices[0]));
    this->fixedParticleIndicesBufferObject->release();
}

void Canvas::updateSpringBuffer(QVector<int> indices)
{
    this->springIndicesBufferObject->bind();
    this->springIndicesBufferObject->allocate(indices.data(), indices.size() * sizeof(indices[0]));
    this->springIndicesBufferObject->release();
}

void Canvas::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (isAllocated(this->locationBufferObject)) {
        this->shaderProgram->bind();
        this->gridArrayObject.bind();
        setMvpValue();
        drawFreeParticles();
        drawFixedParticles();
        drawSprings();
        this->gridArrayObject.release();
        this->shaderProgram->release();
    }
}

void Canvas::setMvpValue()
{
    constructModelViewProjectionMatrix();
    this->shaderProgram->setUniformValue("mvpMatrix", mvpMatrix);
}

void Canvas::setColorValue(QColor color)
{
    this->shaderProgram->setUniformValue("color", color);
}

void Canvas::constructModelViewProjectionMatrix()
{
    mvpMatrix.setToIdentity();
    mvpMatrix.scale(this->zoomingFactor);
    mvpMatrix.rotate(this->rotationAngle, 0.0, 0.0, 1.0);
}

bool Canvas::isAllocated(QOpenGLBuffer *buffer)
{
    return buffer->size() != 0;
}

void Canvas::drawFreeParticles()
{ // Todo: remove magic.
    setColorValue(QColor(Qt::red));
    this->freeParticleIndicesBufferObject->bind();
    glPointSize(8.0f);
    glDrawElements(GL_POINTS, this->numFreeParticles, GL_UNSIGNED_INT, (void*)(0));
    this->freeParticleIndicesBufferObject->release();
}

void Canvas::drawFixedParticles()
{ // Todo: remove magic.
    setColorValue(QColor(Qt::blue));
    this->fixedParticleIndicesBufferObject->bind();
    glPointSize(16.0f);
    glDrawElements(GL_POINTS, this->numFixedParticles, GL_UNSIGNED_INT, (void*)(0));
    this->fixedParticleIndicesBufferObject->release();
}

void Canvas::drawSprings()
{
    setColorValue(QColor(Qt::green));
    this->springIndicesBufferObject->bind();
    glDrawElements(GL_LINES, this->numSprings * 2, GL_UNSIGNED_INT, (void*)(0));
    this->springIndicesBufferObject->release();
}

void Canvas::reset()
{
    this->zoomingFactor = 1.0;
    this->rotationAngle = 1.0;
    this->mvpMatrix.setToIdentity();
}

void Canvas::build(Grid *grid)
{
    QVector<QVector3D> locations = grid->getParticleLocations();
    locations = mapLocationsToRange(locations, grid->getSettings(), -1.0, 1.0);
    updateLocationBuffer(locations);

    QVector<FreeParticle*> freeParticles = grid->getFreeParticles();
    QVector<int> freeParticleIndices = buildFreeParticleIndices(freeParticles);
    updateFreeParticleBuffer(freeParticleIndices);

    // Check if this is needed.
    QVector<FixedParticle*> fixedParticles = grid->getFixedParticles();
    QVector<int> fixedParticleIndices = buildFixedParticleIndices(fixedParticles);
    updateFixedParticleBuffer(fixedParticleIndices);

    QList<Spring> springs = grid->getSprings();
    QVector<int> springIndices = buildSpringIndices(springs);
    updateSpringBuffer(springIndices);
}

QVector<int> Canvas::buildFreeParticleIndices(QVector<FreeParticle*> freeParticles)
{
    this->numFreeParticles = freeParticles.size();
    QVector<int> freeParticleIndices;
    for (int i = 0; i < this->numFreeParticles; i++)
    {
        if(!freeParticles.at(i)->isDisconnected()) {
            freeParticleIndices.append(freeParticles.at(i)->getGlobalID());
        }
    }
    return freeParticleIndices;
}

QVector<int> Canvas::buildFixedParticleIndices(QVector<FixedParticle*> fixedParticles)
{
    this->numFixedParticles = fixedParticles.size();
    QVector<int> fixedParticleIndices;
    for (int i = 0; i < this->numFixedParticles; i++)
    {
        fixedParticleIndices.append(fixedParticles.at(i)->getGlobalID());
    }
    return fixedParticleIndices;
}

QVector<int> Canvas::buildSpringIndices(QList<Spring> springs)
{
    this->numSprings = springs.size();
    QVector<int> springLocationIndices;
    Particle *a, *b;
    Spring spring;

    for (int i = 0; i < this->numSprings; i++)
    {
        spring = springs.at(i);

        if(!spring.isBroken()) {
            a = spring.getParticleA();
            b = spring.getParticleB();

            springLocationIndices.append(a->getGlobalID());
            springLocationIndices.append(b->getGlobalID());
        }
    }
    return springLocationIndices;
}

QVector<QVector3D> Canvas::mapLocationsToRange(QVector<QVector3D> locations, Grid::Settings* settings, float start, float end)
{
    float slope = (end - start) / (static_cast<float>(settings->rows) - 1.0);

    QVector3D mappedLocation;
    for (int i = 0; i < locations.size(); i++)
    {
        mappedLocation = locations.at(i);
        mappedLocation.setX((mappedLocation.x() * slope) + start);
        mappedLocation.setY((mappedLocation.y() * slope) + start);
        locations.replace(i, mappedLocation);
    }
    return locations;
}

bool Canvas::event(QEvent *event)
{
    if (event->type() == QEvent::Gesture) {
          return gestureEvent(static_cast<QGestureEvent*>(event));
    }
    return QWidget::event(event);
}

bool Canvas::gestureEvent(QGestureEvent *event)
{
    if (QGesture *pinch = event->gesture(Qt::PinchGesture)) {
        pinchTriggered(static_cast<QPinchGesture *>(pinch));
    }
    return true;
}

void Canvas::pinchTriggered(QPinchGesture *gesture)
{
    QPinchGesture::ChangeFlags changeFlags = gesture->changeFlags();
    if(changeFlags & QPinchGesture::RotationAngleChanged) {
        this->rotationAngle = -1.0 * gesture->rotationAngle();
    }
    if(changeFlags & QPinchGesture::ScaleFactorChanged) {
        this->zoomingFactor = gesture->scaleFactor();
    }
    if (gesture->state() == Qt::GestureFinished) {
        qDebug() << "Never happens...";
   }
    update();
}
