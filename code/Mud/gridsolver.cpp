#include "gridsolver.h"

GridSolver::GridSolver(Grid *grid, QObject *parent) :
    QObject(parent),
    grid(grid),
    springConstantsMatrix(grid->numSprings(), grid->numSprings()),
    adjacencyMatrix(grid->numSprings(), grid->numFreeParticles())
{
    buildSpringConstantMatrix();
    buildAdjacencyMatrix();
}

void GridSolver::solve()
{
    qDebug() << "solve";
    arma::SpMat<float> lhs = computeLHS();
}

void GridSolver::buildSpringConstantMatrix()
{
    int numSprings = grid->numSprings();
    arma::Col<float> springConstants = arma::Col<float>(numSprings);
    for(const Spring &spring : grid->getSprings())
    {
        springConstants(spring.getId()) = -1 * spring.getSpringConstant();
    }
    springConstantsMatrix.diag() = springConstants;
}

void GridSolver::buildAdjacencyMatrix()
{
    for(const Particle *particle : grid->getParticles())
    {
        if(!particle->isFixed()) {
            for(const Spring *spring : particle->getSprings())
            {
                adjacencyMatrix(spring->getId(), particle->getId()) = 1.0;
            }
        }
    }
}

arma::SpMat<float> GridSolver::computeLHS()
{
    arma::SpMat<float> lhs = arma::SpMat<float>(grid->numSprings(), grid->numFreeParticles());
    lhs = adjacencyMatrix.t() * springConstantsMatrix * adjacencyMatrix;
    lhs.diag() *= -1;
    return lhs;
}


