#include "grid.h"
#include <QDebug>

Grid::Grid(QObject *parent) : QObject(parent)
{
    qDebug() << "Constructor Grid";
}

Grid::~Grid()
{
     qDebug() << "Destructor Grid";

//     delete &particleLocations;
//     delete particles;
//     delete springs;
}

void Grid::gridFactory(Settings settings)
{
    switch(settings.type)
    {
    case SQUARE:
        selectGridCreator(settings, &Grid::uniformSquareGrid, &Grid::variableSquareGrid);
        break;
    case HEXAGONAL:
        selectGridCreator(settings, &Grid::uniformHexagonalGrid, &Grid::variableHexagonalGrid);
        break;
    }
}

void Grid::selectGridCreator(Settings settings, gridCreator uniform, gridCreator variable)
{
    switch(settings.typeDistribution)
    {
    case UNIFORM:
        (this->*uniform)();
        break;
    case VARIABLE:
        (this->*variable)();
        break;
    }
}

void Grid::uniformSquareGrid()
{
    qDebug() << "uniformSquareGrid kinda implemented.";

    this->particles.clear();
    this->particleLocations.clear();
    this->springs.clear();

    this->particles.reserve(4);
    this->particleLocations.reserve(4);
    this->springs.reserve(4);

    Particle *a = addParticle(QVector3D(0.0, 0.0, 0.0));
    Particle *b = addParticle(QVector3D(1.0, 0.0, 0.0));
    Particle *c = addParticle(QVector3D(0.0, 1.0, 0.0));
    Particle *d = addParticle(QVector3D(1.0, 1.0, 0.0));

    addSpring(Spring(a, b));
    addSpring(Spring(b, c));
    addSpring(Spring(c, d));
    addSpring(Spring(d, a));
}

Particle* Grid::addParticle(QVector3D location)
{
    this->particleLocations.append(location);
    QVector3D *locationPtr = &(this->particleLocations.last());

    Particle particle = Particle(locationPtr);
    this->particles.append(particle);
    return &(this->particles.last());
}

void Grid::addSpring(Spring spring)
{
    this->springs.append(spring);
    Spring *springPtr = &(this->springs.last());

    spring.getParticleA()->addSpring(springPtr);
    spring.getParticleB()->addSpring(springPtr);
}


void Grid::variableSquareGrid()
{
    qDebug() << "variableSquareGrid not implemented yet.";
}

void Grid::uniformHexagonalGrid()
{
    qDebug() << "uniformHexagonalGrid not implemented yet.";
}

void Grid::variableHexagonalGrid()
{
    qDebug() << "variableHexagonalGrid not implemented yet.";
}

QDebug operator<<(QDebug stream, const Grid &grid)
{
    stream << "Grid ["
           << "particles: "             << grid.particles           << &endl
           << "particle locations: "    << &endl
           << "\t"                      << grid.particleLocations   << &endl
           << "springs: "               << grid.springs             << &endl
           << "]" << &endl;
    return stream;
}
