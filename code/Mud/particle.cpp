#include "particle.h"

int Particle::nextId = 0;

Particle::Particle(QVector3D *location, bool fixed) :
    location(location),
    fixed(fixed)
{
    id = nextId++;
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

void Particle::clear()
{
    Particle::nextId = 0;
}

bool Particle::isFixed() const
{
    return fixed;
}

QDebug operator<<(QDebug stream, const Particle &particle)
{
    stream << &endl
           << "\tParticle ["
           << "  id: "         <<  particle.id
           << "\tlocation: "   <<  (particle.location ? *(particle.location) : QVector3D(-1.0, -1.0, -1.0))
           << "\tsprings: "    <<  particle.springs
           << "\tfixed: "      <<  particle.isFixed()
           << "]";
    return stream;
}
