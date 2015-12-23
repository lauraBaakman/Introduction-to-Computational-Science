#include "grid.h"
#include <QDebug>

Grid::Grid(QObject *parent) : QObject(parent)
{
    qDebug() << "Constructor Grid";
}

Grid::~Grid()
{
    qDebug() << "Destructor Grid";
    for(const Particle* particle : particles){
        delete particle;
    }
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

int Grid::numSprings()
{
    return this->springs.size();
}

int Grid::numFreeParticles()
{
    return freeParticles.size();
}

QVector<Spring> Grid::getSprings() const
{
    return springs;
}

Spring Grid::getSpring(int index) const
{
    return springs.at(index);
}

QVector<Particle *> Grid::getParticles() const
{
    return particles;
}

QVector<FreeParticle *> Grid::getFreeParticles() const
{
    return freeParticles;
}

void Grid::clear()
{
    this->particles.clear();
    this->particleLocations.clear();
    this->springs.clear();
    this->freeParticles.clear();

    FreeParticle::clear();
    FixedParticle::clear();
    Spring::clear();
}

void Grid::reserve(int numParticles, int numSprings)
{
    this->particles.reserve(numParticles);
    this->particleLocations.reserve(numParticles);
    this->springs.reserve(numSprings);
    this->freeParticles.reserve(numParticles);
}

Particle* Grid::addParticle(QVector3D location, Particle* particle)
{
    QVector3D* locationPtr = this->addParticleLocation(location);
    particle->setLocation(locationPtr);

    return addParticle(particle);
}

//Assumes that the particle location is already in the list of particle locations!

//TODO use overloaded method!
Particle *Grid::addParticle(Particle *particle)
{
    this->particles.append(particle);
    if(!particle->isFixed()){
        freeParticles.append(dynamic_cast<FreeParticle*>(particle));
    }
    return particle;
}

QVector3D *Grid::addParticleLocation(QVector3D location)
{
    this->particleLocations.append(location);
    QVector3D *locationPtr = &(this->particleLocations.last());
    return locationPtr;
}

void Grid::addSpring(Spring spring)
{
    this->springs.append(spring);
    Spring *springPtr = &(this->springs.last());

    spring.getParticleA()->addSpring(springPtr);
    spring.getParticleB()->addSpring(springPtr);
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

    clear();
//    reserve(4, 5);

//    Particle *a = addParticle(QVector3D(0.0, 1.0, 0.0));
//    Particle *b = addParticle(QVector3D(1.0, 1.0, 0.0));
//    Particle *c = addParticle(QVector3D(0.0, 0.0, 0.0));
//    Particle *d = addParticle(QVector3D(1.0, 0.0, 0.0));

//    addSpring(Spring(a, b));
//    addSpring(Spring(b, c));
//    addSpring(Spring(c, d));
//    addSpring(Spring(d, a));
//    addSpring(Spring(a, c));
}

void Grid::variableSquareGrid()
{
    qDebug() << "variableSquareGrid kinda implemented. But not really...";

    clear();
    reserve(3, 3);

    Particle *a = addParticle(QVector3D(0.0, 1.0, 0.0), new FixedParticle());
    Particle *b = addParticle(QVector3D(1.0, 0.0, 0.0), new FreeParticle());
    Particle *c = addParticle(QVector3D(0.0, 0.0, 0.0), new FreeParticle());

    addSpring(Spring(a, c));
    addSpring(Spring(a, b));
    addSpring(Spring(b, c));
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
           << "\tparticles: "               << grid.particles           << &endl
           << "\tparticle locations: "                                  << &endl
           << "\t"                          << grid.particleLocations   << &endl
           << "\tsprings: "                 << grid.springs             << &endl
           << "]" << &endl;
    return stream;
}

QDebug operator<<(QDebug stream, Grid *grid)
{
    stream << *grid;
    return stream;
}
