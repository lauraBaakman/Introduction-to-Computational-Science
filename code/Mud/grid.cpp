#include "grid.h"
#include <QDebug>
#include <math.h>

Grid::Grid(QObject *parent) : QObject(parent)
{
    //qDebug() << "Constructor Grid";
}

Grid::~Grid()
{
    //qDebug() << "Destructor Grid";
    for(const Particle* particle : particles){
        delete particle;
    }
}

void Grid::gridFactory(Settings settings)
{
    this->settings = settings;

    switch(settings.type)
    {
    case SQUARE:
        selectGridCreator(&Grid::uniformSquareGrid, &Grid::variableSquareGrid);
        break;
    case HEXAGONAL:
        selectGridCreator(&Grid::uniformHexagonalGrid, &Grid::variableHexagonalGrid);
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

QVector<QVector3D> Grid::getParticleLocations() const
{
    return particleLocations;
}

QVector<FixedParticle *> Grid::getFixedParticles() const
{
    return fixedParticles;
}

void Grid::breakSprings()
{
    qDebug() << "Grid::breakSprings() needs a decent implementation!";
    breakSpringsWithHighestStrain(2);
}

void Grid::breakSpringsWithHighestStrain(int springsToBreak)
{
    std::map<float, Spring*> map;

    for (QVector<Spring>::iterator spring = springs.begin(); spring != springs.end(); spring++) {
        if(!spring->isBroken()) map[spring->strain()] = spring;
    }

    for(auto item = map.begin();
        (springsToBreak != 0) && (item != map.end());
        item++)
    {
        item->second->breakIt();
        springsToBreak--;
    }
}

void Grid::breakSpringsWithStrainGreaterThan(float breakingStrain)
{
    for (QVector<Spring>::iterator spring = springs.begin(); spring != springs.end(); spring++) {
        if(spring->strain() > breakingStrain) spring->breakIt();
    }
}

void Grid::clear()
{
    this->particles.clear();
    this->particleLocations.clear();
    this->springs.clear();
    this->freeParticles.clear();
    this->fixedParticles.clear();

    FreeParticle::clear();
    FixedParticle::clear();
    Particle::clear();
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
    QVector3D* locationPtr = this->addParticleLocation(location, particle->getGlobalID());
    particle->setLocation(locationPtr);
    return addParticle(particle);
}

//Assumes that the particle location is already in the list of particle locations!
Particle *Grid::addParticle(Particle *particle)
{
    this->particles.insert(particle->getGlobalID(), particle);
    if(particle->isFixed()) {
        fixedParticles.insert(
                    particle->getId(),
                    dynamic_cast<FixedParticle*>(particle));
    } else {
        freeParticles.insert(
                    particle->getId(),
                    dynamic_cast<FreeParticle*>(particle));
    }
    return particle;
}

QVector3D *Grid::addParticleLocation(QVector3D location, int globalParticleId)
{
    particleLocations.insert(globalParticleId, location);
    QVector3D *locationPtr = &(this->particleLocations.last());
    return locationPtr;
}

void Grid::addSpring(Spring spring)
{
    springs.append(spring);
    Spring *springPtr = &(this->springs.last());

    spring.getParticleA()->addSpring(springPtr);
    spring.getParticleB()->addSpring(springPtr);
}

Grid::Settings* Grid::getSettings()
{
    return &this->settings;
}

void Grid::selectGridCreator(gridCreator uniform, gridCreator variable)
{
    switch(this->settings.typeDistribution)
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
    clear();

    int rows = ceil(sqrt(this->settings.numParticles));
    int columns = rows;
    this->settings.rows = rows;
    this->settings.columns = columns;

    int numParticles = rows * columns;
    int numSprings = (2 *(columns * rows + 2)) - (3 * (rows + columns));

    reserve(numParticles, numSprings);

    for (int row = 0; row < rows; row++)
    {
        for(int column = 0; column < columns; column++)
        {
            if(onBorder(row, column, rows, columns) &&
                    !onCorner(row, column, rows, columns))
            { // Fixed border particles
                addParticle(QVector3D((float)row, (float)column, 0.0), new FixedParticle());
            } else if (!onBorder(row, column, rows, columns))
            { // Free particles
                addParticle(QVector3D((float) row, (float) column, 0.0), new FreeParticle());
            }
        }
    }
}

bool Grid::onCorner(int row, int column, int rows, int columns)
{
    bool cornerColumn = (column == 0 || column == (columns - 1));
    return (row == 0 && cornerColumn) || (row == (rows - 1) && cornerColumn);
}

bool Grid::onBorder(int row, int column, int rows, int columns)
{
    return row == 0 || row == (rows - 1) || column == 0 || column == (columns - 1);
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
           << "\tfree particles: "                                      << &endl
           << "\t"                          << grid.freeParticles       << &endl
           << "\tfixed particles: "                                     << &endl
           << "\t"                          << grid.fixedParticles      << &endl
           << "\tsprings: "                 << grid.springs             << &endl
           << "]" << &endl;
    return stream;
}

QDebug operator<<(QDebug stream, Grid *grid)
{
    stream << *grid;
    return stream;
}
