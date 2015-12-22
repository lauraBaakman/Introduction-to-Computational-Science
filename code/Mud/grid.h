#ifndef GRID_H
#define GRID_H

#include <QVector>
#include <QObject>

#include "particle.h"
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

private:
    QVector<Particle> particles;
    QVector<QVector3D> particleLocations;

    QVector<Spring> springs;

    Particle* addParticle(QVector3D location);
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
