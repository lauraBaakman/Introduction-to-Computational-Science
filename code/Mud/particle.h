#ifndef PARTICLE_H
#define PARTICLE_H

#include <QVector>
#include <QVector3D>
#include <QDebug>

#include "spring.h"

class Spring;

class Particle
{
public:
    Particle(QVector3D *location = nullptr);

    void addSpring(Spring *const spring);

    friend QDebug operator<<(QDebug stream, const Particle &particle);

    QVector3D *getLocation() const;

private:
    QVector3D *location;
    // Force?
    QVector<Spring*> springs;
};

#endif // PARTICLE_H
