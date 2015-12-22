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

    QVector<Spring> getSprings() const;
    Spring getSpring(int index) const;

    QVector<Particle *> getParticles() const;

private:
    QVector<Particle *> particles;
    QVector<QVector3D> particleLocations;

    QVector<Spring> springs;

    void clear();
    void reserve(int numParticles, int numSprings);

    Particle* addFreeParticle(QVector3D location);
    Particle* addParticle(Particle *particle);

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
