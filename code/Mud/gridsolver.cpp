#include "gridsolver.h"

GridSolver::GridSolver(Grid *grid, QObject *parent) :
    QObject(parent),
    grid(grid),
    springConstantsMatrix(grid->numSprings(), grid->numSprings()),
    adjacencyMatrix(grid->numSprings(), grid->numFreeParticles())
{
    qDebug() << "GridSolver constructor";
    buildSpringConstantMatrix();
}


void GridSolver::buildSpringConstantMatrix()
{
    int numSprings = grid->numSprings();
    arma::Col<float> springConstants = arma::Col<float>(numSprings);
    for(const Spring &spring : grid->getSprings())
    {
        springConstants(spring.getId()) = spring.getSpringConstant();
    }
    springConstantsMatrix.diag() = springConstants;
}

void GridSolver::buildAdjacencyMatrix()
{
    for(const Particle &particle : grid->getParticles())
    {
        for(const Spring &spring : particle->getFreeSprings())
        {

        }
    }
}


