#include "particle.h"

Particle::Particle(QVector3D *location) :
    location(location)
{
    //constructor body
}

Particle::~Particle(){
    qDebug() << "Particle deconstructor";
}

void Particle::addSpring(Spring *const spring)
{
    springs.append(spring);
}

QVector3D *Particle::getLocation() const
{
    return location;
}

QDebug Particle::doPrint(QDebug stream) const {
    stream <<   "  id: "         <<  id
           <<   "\tlocation: "   <<  (location ? *(location) : QVector3D(-1.0, -1.0, -1.0))
           <<   "\tsprings: "    <<  springs;
    return stream;
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
