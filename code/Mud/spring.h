#ifndef SPRING_H
#define SPRING_H

#include <random>
#include <iostream>

#include <QDebug>
#include <QVector3D>

#include "particle.h"

class Particle;

class Spring
{
public:
    Spring(
            Particle *particleA = nullptr, Particle *particleB = nullptr,
            bool broken = false, float naturalLength = 0);

    friend QDebug operator<<(QDebug stream, const Spring &spring);
    friend QDebug operator<<(QDebug stream, Spring *spring);

    Particle *getParticleA() const;
    Particle *getParticleB() const;

    float getSpringConstant() const;

    const Particle *getOtherParticle(const Particle* particle) const;

    float strain() const;

    int getId() const;
    static void clear();

    static void setSpringConstantDistributionParameters(float mean = 0.0, float standardDeviation = 1.0);

private:
    float springConstant;
    float naturalLength;
    bool broken;
    int id;

    Particle *particleA;
    Particle *particleB;

    float sampleSpringConstant();

    static int nextId;

    static std::normal_distribution<float> normalDistribution;
    static std::default_random_engine randomNumberGenerator;

};

#endif // SPRING_H
