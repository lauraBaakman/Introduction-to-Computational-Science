#include "gridsolver.h"

GridSolver::GridSolver(QObject *parent, Grid *grid) :
    QObject(parent),
    grid(grid),
    springConstantsMatrix(grid->numSprings(), grid->numSprings()),
    adjacencyMatrix(grid->numSprings(), grid->numFreeParticles())
{

}

