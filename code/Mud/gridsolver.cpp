#include "gridsolver.h"

GridSolver::GridSolver(Grid *grid, QObject *parent) :
    QObject(parent),
    grid(grid),
    springConstantsMatrix(grid->numSprings(), grid->numSprings()),
    adjacencyMatrix(grid->numSprings(), grid->numFreeParticles())
{
    qDebug() << "GridSolver constructor";

    qDebug() << grid->numSprings();
    qDebug() << grid->numFreeParticles();

    buildSpringConstantMatrix();
    buildAdjacencyMatrix();
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
//    for(const Particle &particle : grid->getParticles())
//    {
//        if(!particle.isFixed()) {
//            for(const Spring *spring : particle.getSprings())
//            {
//                qDebug() << spring->getId() << " " << particle.getId();
//                adjacencyMatrix(spring->getId(), particle.getId()) = 1.0;
//            }
//        }
//    }
//    std::cout << adjacencyMatrix;
}


