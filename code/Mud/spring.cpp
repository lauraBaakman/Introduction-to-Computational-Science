#include "spring.h"

int Spring::nextId = 0;
std::default_random_engine Spring::generator;

Spring::Spring(Particle *particleA, Particle *particleB, bool broken) :
    broken(broken),
    particleA(particleA),
    particleB(particleB)
{
    id = nextId++;
    springConstant = sampleSpringConstant();
}

Particle *Spring::getParticleA() const
{
    return particleA;
}

Particle *Spring::getParticleB() const
{
    return particleB;
}

float Spring::getSpringConstant() const
{
    return springConstant;
}

const Particle *Spring::getOtherParticle(const Particle *particle) const
{
    if(particleA == particle) return particleB;
    if(particleB == particle) return particleA;
    return particle;
}

void Spring::clear()
{
    Spring::nextId = 0;
}

void Spring::setSpringConstantDistributionParameters(float mean, float standardDeviation)
{
    //TODO implement
    qDebug() << "Implement the function setSpringConstantDistributionParameters!";
    exit(-1);
}

float Spring::sampleSpringConstant()
{
    std::normal_distribution<double> distribution(5.0,2.0);

    float number = distribution(Spring::generator);
    qDebug() << "Generating a random number: " << number << &endl;
    return number;
}

int Spring::getId() const
{
    return id;
}

QDebug operator<<(QDebug stream, const Spring &spring)
{
    stream << &endl
           << "\tSpring ["
           << "\tparticle: "        << (spring.particleA ? *(spring.particleA->getLocation()) : QVector3D(-1.0, -1.0, -1.0))
           << "\tparticle: "        << (spring.particleB ? *(spring.particleB->getLocation()) : QVector3D(-1.0, -1.0, -1.0))
           << "\tspring constant: " << spring.springConstant
           << "\tbroken: "          << spring.broken
           << "\tid: "              << spring.getId()
           << "]";
    return stream;
}

QDebug operator<<(QDebug stream, Spring* spring){
    stream << spring->id;
    return stream;
}
