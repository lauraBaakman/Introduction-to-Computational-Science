#include "grid.h"
#include <QDebug>

Grid::Grid(QObject *parent) : QObject(parent)
{
    qDebug() << "Constructor Grid";
}

Grid::~Grid()
{
     qDebug() << "Destructor Grid";
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

    particles.clear();
    particleLocations.clear();
    springs.clear();

    QVector3D *particleLocation = new QVector3D(0.0, 0.0, 0.0);
    // Function add particle
    particleLocations.append(*particleLocation);
    Particle *particleA = new Particle(particleLocation);
    particles.append(*particleA);

    particleLocation = new QVector3D(1.0, 1.0, 0.0);
    // Function add particle
    particleLocations.append(*particleLocation);
    Particle *particleB = new Particle(particleLocation);
    particles.append(*particleB);

    particleLocation = new QVector3D(1.0, 0.0, 0.0);
    // Function add particle
    particleLocations.append(*particleLocation);
    Particle *particleC = new Particle(particleLocation);
    particles.append(*particleC);

    particleLocation = new QVector3D(0.0, 1.0, 0.0);
    // Function add particle
    particleLocations.append(*particleLocation);
    Particle *particleD = new Particle(particleLocation);
    particles.append(*particleD);

    Spring *springA = new Spring(particleA, particleB);
    particleA->addSpring(springA);
    particleB->addSpring(springA);
    springs.append(*springA);

    Spring *springB = new Spring(particleB, particleC);
    particleB->addSpring(springB);
    particleC->addSpring(springB);
    springs.append(*springB);

    Spring *springC = new Spring(particleC, particleD);
    particleC->addSpring(springC);
    particleD->addSpring(springC);
    springs.append(*springC);

    Spring *springD = new Spring(particleD, particleA);
    particleD->addSpring(springD);
    particleA->addSpring(springD);
    springs.append(*springD);

//    this->addParticle(new Particle())

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
