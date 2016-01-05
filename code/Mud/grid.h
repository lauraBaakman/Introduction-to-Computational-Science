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
//        int width;
//        int height;
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

    void breakSpringsWithHighestStrain(int numSpringsToBreak);
    void breakSpringsWithStrainGreaterThan(float breakingStrain);


    QVector<Spring> springs;

    void clear();
    void reserve(int numParticles, int numSprings);

    Particle* addParticle(QVector3D location, Particle* particle);
    Particle* addParticle(Particle* particle);

    QVector3D* addParticleLocation(QVector3D location, int globalParticleId);

    void addSpring(Spring spring);

    void uniformSquareGrid();
    void variableSquareGrid();

    void uniformHexagonalGrid();
    void variableHexagonalGrid();

    typedef void (Grid::*gridCreator)();
    void selectGridCreator(Settings settings, gridCreator uniform, gridCreator variable);
signals:

public slots:
};

#endif // GRID_H
