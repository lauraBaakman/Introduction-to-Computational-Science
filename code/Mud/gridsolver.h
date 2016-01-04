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
    typedef void (QVector3D::*elementSetter)(float);

    arma::Col<float> solveForAxis(arma::Mat<float> lhs, elementGetter getter);

    void updateLocations(arma::Mat<float> newLocations);

    arma::Mat<float> springConstantsMatrix;
    arma::Mat<float> adjacencyMatrix;

    void buildSpringConstantMatrix();
    void buildAdjacencyMatrix();

    arma::Mat<float> computeLHS();
    float computeVectorElement(const Particle* particle, elementGetter getter);
    arma::Col<float> computeRHS(elementGetter getter);

signals:

public slots:
};

#endif // GRIDSOLVER_H
