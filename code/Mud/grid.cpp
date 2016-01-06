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
    clear();

    Spring::setSpringConstantDistributionParameters(settings.springConstantmean, settings.springConstantSD);

    setBreakMethod(settings);
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

float Grid::energy()
{
    float energy = 0;
    for (auto particle:particles)
    {
        energy += particle->energy();
    }
    return energy;
}

void Grid::setBreakMethod(Grid::SpringBreakMethod method)
{
    switch(method){
    case SPRINGS_WITH_STRAIN_GREATER_THAN:
        breakSprings = &Grid::breakSpringsWithStrainGreaterThan;
        break;
    case X_SPRINGS_WITH_HIGHEST_STRAIN: //fall through
    default:
        breakSprings = &Grid::breakSpringsWithHighestStrain;
        break;
    }
}

void Grid::setBreakMethodParameter(float parameter)
{
    settings.springBreakParameter = parameter;
}

void Grid::setBreakMethod(Grid::Settings settings)
{
    setBreakMethod(settings.springBreakMethod);
}

void Grid::breakSpringsWithHighestStrain()
{
    std::map<float, Spring*> map;

    int springsToBreak = settings.springBreakParameter;

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

void Grid::breakSpringsWithStrainGreaterThan()
{
    float breakingStrain = settings.springBreakParameter;
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
    // Get a bunch of numbers.
    int rows = ceil(sqrt(this->settings.numParticles));
    int columns = rows;
    int numParticles = rows * columns;
    int numSprings = (2 *(columns * rows + 2)) - (3 * (rows + columns));

    // Updating settings struct of grid.
    this->settings.rows = rows;
    this->settings.columns = columns;
    this->settings.numParticles = numParticles;

    // Memory
    reserve(numParticles, numSprings);

    Particle *left = nullptr;
    Particle *center = nullptr;
    Particle *top = nullptr;

    // Klap dit stukje maar gewoon even dicht...
    for (int row = 0; row < rows; row++)
    {
        for(int column = 0; column < columns; column++)
        {
            if(onBorder(row, column, rows, columns) &&
                    !onCorner(row, column, rows, columns))
            { // Fixed border particles
                 center = addParticle(QVector3D((float)column, (float)row, 0.0), new FixedParticle());
                 // Add springs...
                 if(left != nullptr && !left->isFixed()){addSpring(Spring(center, left));}
                 if(row == (rows - 1)) {
                     top = getParticleById(fromCoordinateToId(row - 1, column, rows, columns));
                     addSpring(Spring(center, top));
                 }
            } else if (!onBorder(row, column, rows, columns)) { // Free particles
                center = addParticle(QVector3D((float)column, (float)row, 0.0), new FreeParticle());
                // Add springs...
                if (left != nullptr) {addSpring(Spring(center, left));}
                top = getParticleById(fromCoordinateToId(row - 1, column, rows, columns));
                addSpring(Spring(center, top));
            }
            left = center;
        }
    }
}

int Grid::fromCoordinateToId(int row, int column, int rows, int columns)
{
    int corners = 1;
    if(row > 0 && row < (rows - 1)) {
        corners = 2;
    } else if (row == (rows - 1)) {
        corners = 3;
    }
    return ((row * columns) + column) - corners;
}

Particle *Grid::getParticleById(int id)
{
    for(int i = 0; i < this->particles.size(); i++)
    {
        Particle *particle = particles.at(i);
        if(particle->getGlobalID() == id)
        {
            return particle;
        }
    }
    qDebug() << "getParticleById could not find the particle with id " << id;
    return nullptr;
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
//           << "\tparticle locations: "                                  << &endl
//           << "\t"                          << grid.particleLocations   << &endl
//           << "\tfree particles: "                                      << &endl
//           << "\t"                          << grid.freeParticles       << &endl
//           << "\tfixed particles: "                                     << &endl
//           << "\t"                          << grid.fixedParticles      << &endl
           << "\tsprings: "                 << grid.springs             << &endl
           << "]" << &endl;
    return stream;
}

QDebug operator<<(QDebug stream, Grid *grid)
{
    stream << *grid;
    return stream;
}
