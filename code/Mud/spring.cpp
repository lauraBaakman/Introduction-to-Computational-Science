#include "spring.h"

int Spring::nextId = 0;
std::default_random_engine Spring::random_number_generator;

//Create the normal distribution with the default argumetns: mean = 0, std = 1
std::normal_distribution<float> Spring::normalDistribution;

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
    Spring::normalDistribution = std::normal_distribution<float> (mean, standardDeviation);
}

float Spring::sampleSpringConstant()
{
    float number = Spring::normalDistribution(Spring::random_number_generator);
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
