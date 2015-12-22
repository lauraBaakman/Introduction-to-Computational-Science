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

int Grid::numSprings()
{
    return this->springs.size();
}

int Grid::numFreeParticles()
{ // TODO: Make it a property and build it on initialisation.
    int count = 0;
    for(const Particle *particle : this->particles)
    {
        if(!particle->isFixed())
        {
            count++;
        }
    }
    return count;
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

void Grid::clear()
{
    this->particles.clear();
    this->particleLocations.clear();
    this->springs.clear();

    FreeParticle::clear();
    FixedParticle::clear();

    Spring::clear();
}

void Grid::reserve(int numParticles, int numSprings)
{
    this->particles.reserve(numParticles);
    this->particleLocations.reserve(numParticles);
    this->springs.reserve(numSprings);
}

Particle* Grid::addFreeParticle(QVector3D location)
{
    return addParticle(new FreeParticle(&location));
}

Particle* Grid::addParticle(Particle *particle)
{
    this->particleLocations.append(*(particle->getLocation()));
    QVector3D *locationPtr = &(this->particleLocations.last());
    particle->setLocation(locationPtr);


    //TODO: Delete particle?
    this->particles.append(particle);
    return this->particles.last();
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
    reserve(4, 5);

    Particle *a = addFreeParticle(QVector3D(0.0, 1.0, 0.0));
    Particle *b = addFreeParticle(QVector3D(1.0, 1.0, 0.0));
    Particle *c = addFreeParticle(QVector3D(0.0, 0.0, 0.0));
    Particle *d = addFreeParticle(QVector3D(1.0, 0.0, 0.0));

    addSpring(Spring(a, b));
    addSpring(Spring(b, c));
    addSpring(Spring(c, d));
    addSpring(Spring(d, a));
    addSpring(Spring(a, c));
}

void Grid::variableSquareGrid()
{
    qDebug() << "variableSquareGrid kinda implemented. But not really...";

    clear();
    reserve(3, 3);

    // TODO: Fix the new -> possible memory leaks...
    Particle *a = addParticle(new FixedParticle(new QVector3D(0.0, 1.0, 0.0)));
    Particle *b = addFreeParticle(QVector3D(1.0, 0.0, 0.0));
    Particle *c = addFreeParticle(QVector3D(0.0, 0.0, 0.0));

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
           << "particles: "             << grid.particles           << &endl
           << "particle locations: "    << &endl
           << "\t"                      << grid.particleLocations   << &endl
           << "springs: "               << grid.springs             << &endl
           << "]" << &endl;
    return stream;
}
