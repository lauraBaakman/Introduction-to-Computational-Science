#include "particle.h"


Particle::Particle(QVector3D *location) :
    location(location)
{

}

void Particle::addSpring(Spring *const spring)
{
    this->springs.append(spring);
}

QVector3D *Particle::getLocation() const
{
    return location;
}

QDebug operator<<(QDebug stream, const Particle &particle)
{
    stream << "Particle ["
           << (particle.location ? *(particle.location) : QVector3D(-1.0, -1.0, -1.0))
           << particle.springs
           << "]" << &endl;
    return stream;
}
