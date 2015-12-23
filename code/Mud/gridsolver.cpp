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
    arma::Col<float> rhsX = computeRHSx();
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

float computeRHSxElement(const Particle* particle){
    float element = 0;
    const Particle* otherParticle;
    for (const Spring *spring : particle->getSprings()){
        otherParticle = spring->getOtherParticle(particle);
        if(otherParticle->isFixed()){
            element += (spring->getSpringConstant() * otherParticle->getLocation()->x());
        }
    }
    return element;
}

arma::Col<float> GridSolver::computeRHSx()
{
    arma::Col<float> rhs = arma::Col<float>(grid->numFreeParticles());
    QVector<FreeParticle*> freeParticles = grid->getFreeParticles();
    for(const FreeParticle *particle : freeParticles){
        rhs(particle->getId()) = computeRHSxElement(particle);
    }
    std::cout << rhs;
    return rhs;
}
