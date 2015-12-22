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
    for(int i = 0; i < numSprings; i++)
    {
        springConstants(i) = grid->getSpring(i).getSpringConstant();
    }
    springConstantsMatrix.diag() = springConstants;

    std::cout << springConstantsMatrix;
}

void GridSolver::buildAdjacencyMatrix()
{

}


