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
    Particle(QVector3D *location = nullptr, bool fixed = false);

    void addSpring(Spring *const spring);
    bool isFixed() const;

    friend QDebug operator<<(QDebug stream, const Particle &particle);

    QVector3D *getLocation() const;

    void setLocation(QVector3D *value);

private:
    QVector3D *location;
    // Force?
    QVector<Spring*> springs;
    bool fixed;
};

#endif // PARTICLE_H
