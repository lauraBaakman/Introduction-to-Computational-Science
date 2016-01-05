#ifndef GRID_H
#define GRID_H

#include <QVector>
#include <QObject>

#include "freeparticle.h"
#include "fixedparticle.h"

#include "spring.h"

class Grid : public QObject
{
    Q_OBJECT
public:
    enum Type {
        SQUARE,
        HEXAGONAL,
    };

    enum TypeDistribution {
        UNIFORM,
        VARIABLE
    };

    struct Settings {
        Type type;
        TypeDistribution typeDistribution;
        int numParticles;
        int rows;
        int columns;
    };

    explicit Grid(QObject *parent = 0);
    ~Grid();

    void gridFactory(Settings settings);

    int numSprings();
    int numFreeParticles();

    friend QDebug operator<<(QDebug stream, const Grid &grid);
    friend QDebug operator<<(QDebug stream, Grid *grid);

    QVector<Spring> getSprings() const;
    Spring getSpring(int index) const;

    QVector<Particle *> getParticles() const;

    QVector<FreeParticle *> getFreeParticles() const;

    QVector<QVector3D> getParticleLocations() const;

    QVector<FixedParticle *> getFixedParticles() const;

private:
    QVector<Particle *> particles;
    QVector<FreeParticle *> freeParticles;
    QVector<FixedParticle *>  fixedParticles;
    QVector<QVector3D> particleLocations;
    QVector<Spring> springs;

    Settings settings;

    void clear();
    void reserve(int numParticles, int numSprings);

    Particle* addParticle(QVector3D location, Particle* particle);
    Particle* addParticle(Particle* particle);
    Particle* getParticleById(int id);

    QVector3D* addParticleLocation(QVector3D location, int globalParticleId);

    void addSpring(Spring spring);

    void uniformSquareGrid();
    void variableSquareGrid();

    void uniformHexagonalGrid();
    void variableHexagonalGrid();

    bool onBorder(int row, int column, int rows, int columns);
    bool onCorner(int row, int column, int rows, int columns);
    int fromCoordinateToId(int row, int column, int rows, int columns);

    typedef void (Grid::*gridCreator)();
    void selectGridCreator(gridCreator uniform, gridCreator variable);
signals:

public slots:

    Settings* getSettings();
};

#endif // GRID_H
