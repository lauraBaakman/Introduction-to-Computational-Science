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
    arma::Mat<float> lhs = computeLHS();

    arma::Mat<float> solution = arma::Mat<float>(lhs.n_rows, 3);

    //Solve the system
    solution.col(0) = solveForAxis(lhs, &QVector3D::x);
    solution.col(1) = solveForAxis(lhs, &QVector3D::y);
    solution.col(2) = solveForAxis(lhs, &QVector3D::z);

    updateLocations(solution);
}

arma::Col<float> GridSolver::solveForAxis(
        arma::Mat<float> lhs,
        GridSolver::elementGetter getter)
{
    arma::Col<float> rhs = computeRHS(getter);
    arma::Col<float> solution = arma::Col<float>(lhs.n_rows);

    arma::solve(solution, lhs, rhs);
    return solution;
}

void GridSolver::updateLocations(arma::Mat<float> newLocations)
{
    qDebug() << grid->getParticleLocations();
    for (unsigned long long i = 0; i < newLocations.n_rows; i++){
        grid->getParticleLocations()[i].setX(newLocations(i, 1));
    }
    qDebug() << grid->getParticleLocations();
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

arma::Mat<float> GridSolver::computeLHS()
{
    arma::Mat<float> lhs = arma::Mat<float>(grid->numSprings(), grid->numFreeParticles());
    lhs = adjacencyMatrix.t() * springConstantsMatrix * adjacencyMatrix;
    lhs.diag() *= -1;
    return lhs;
}

float GridSolver::computeVectorElement(const Particle* particle, GridSolver::elementGetter getter){
    float element = 0;
    const Particle* otherParticle;

    for (const Spring *spring : particle->getSprings()){
        otherParticle = spring->getOtherParticle(particle);
        if(otherParticle->isFixed()){
            element += (spring->getSpringConstant() * (otherParticle->getLocation()->*getter)());
        }
    }
    return element;
}

arma::Col<float> GridSolver::computeRHS(GridSolver::elementGetter getter)
{
    arma::Col<float> rhs = arma::Col<float>(grid->numFreeParticles());
    QVector<FreeParticle*> freeParticles = grid->getFreeParticles();
    for(const FreeParticle *particle : freeParticles){
        rhs(particle->getId()) = computeVectorElement(particle, getter);
    }
    return rhs;
}
