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
    friend QDebug operator<<(QDebug stream, Spring *spring);

    Particle *getParticleA() const;
    Particle *getParticleB() const;

    float getSpringConstant() const;

    const Particle *getOtherParticle(const Particle* particle) const;

    int getId() const;
    static void clear();

private:
    float springConstant;
    bool broken;

    static int nextId;
    int id;

    Particle *particleA;
    Particle *particleB;
};

#endif // SPRING_H
