#include "particle.h"

int Particle::nextId = 0;

Particle::Particle(QVector3D *location) :
    location(location),
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
