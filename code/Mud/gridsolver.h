#ifndef GRIDSOLVER_H
#define GRIDSOLVER_H

#include <QObject>
#include <armadillo>

#include "grid.h"

using aram;

class GridSolver : public QObject
{
    Q_OBJECT
public:
    GridSolver(QObject *parent = 0, Grid *grid);

    void solve();

private:
    Grid *grid;

    SpMat<float> springConstantsMatrix;
    SpMat<float> adjacencyMatrix;

    void buildSpringConstantMatrix();
    void buildAdjacencyMatrix();

signals:

public slots:
};

#endif // GRIDSOLVER_H
