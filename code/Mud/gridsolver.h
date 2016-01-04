#ifndef GRIDSOLVER_H
#define GRIDSOLVER_H

#include <QObject>
#include <armadillo>

#include "grid.h"

class GridSolver : public QObject
{
    Q_OBJECT
public:
    GridSolver(Grid *grid, QObject *parent = 0);

    void solve();

private:
    Grid *grid;

    typedef float (QVector3D::*elementGetter)() const;

    arma::SpMat<float> springConstantsMatrix;
    arma::SpMat<float> adjacencyMatrix;

    void buildSpringConstantMatrix();
    void buildAdjacencyMatrix();

    arma::SpMat<float> computeLHS();
    float computeVectorElement(const Particle* particle, elementGetter getter);
    arma::Col<float> computeRHS(elementGetter getter);

signals:

public slots:
};

#endif // GRIDSOLVER_H
