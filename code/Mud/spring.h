#ifndef SPRING_H
#define SPRING_H

#include <QDebug>
#include <QVector3D>

#include "particle.h"

class Particle;

class Spring
{
public:
    Spring(Particle *particleA = nullptr, Particle *particleB = nullptr,
           float springConstant = 1.0, bool broken = false);

    friend QDebug operator<<(QDebug stream, const Spring &spring);

    Particle *getParticleA() const;
    Particle *getParticleB() const;

    float getSpringConstant() const;

private:
    float springConstant;
    bool broken;

    Particle *particleA;
    Particle *particleB;

};

#endif // SPRING_H
