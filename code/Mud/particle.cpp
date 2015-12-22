#include "particle.h"

Particle::Particle(QVector3D *location) :
    location(location)
{
    //constructor body
}

void Particle::addSpring(Spring *const spring)
{
    springs.append(spring);
}

QVector3D *Particle::getLocation() const
{
    return location;
}

QDebug operator<<(QDebug stream, const Particle &particle){
    return particle.doPrint(stream);
}

void Particle::setLocation(QVector3D *value)
{
    location = value;
}

QVector<Spring *> Particle::getSprings() const
{
    return springs;
}

int Particle::getId() const
{
    return id;
}
