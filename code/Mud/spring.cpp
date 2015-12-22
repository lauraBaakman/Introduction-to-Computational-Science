#include "spring.h"

Spring::Spring(Particle *particleA, Particle *particleB,
               float springConstant, bool broken) :
    springConstant(springConstant),
    broken(broken),
    particleA(particleA),
    particleB(particleB)
{

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

QDebug operator<<(QDebug stream, const Spring &spring)
{
    stream << &endl
           << "\tSpring ["
           << "\tparticle: "        << (spring.particleA ? *(spring.particleA->getLocation()) : QVector3D(-1.0, -1.0, -1.0))
           << "\tparticle: "        << (spring.particleB ? *(spring.particleB->getLocation()) : QVector3D(-1.0, -1.0, -1.0))
           << "\tspring constant: " <<  spring.springConstant
           << "\tbroken: "          <<  spring.broken
           << "]";
    return stream;
}
