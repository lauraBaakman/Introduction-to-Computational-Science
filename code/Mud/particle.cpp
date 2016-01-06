#include "particle.h"

int Particle::nextGlobalID = 0;

Particle::Particle(QVector3D *location) :
    location(location)
{
    globalID = nextGlobalID++;
}

Particle::~Particle(){
    //destructor body
}

void Particle::addSpring(Spring *const spring)
{
    springs.append(spring);
}

QVector3D *Particle::getLocation() const
{
    return location;
}

void Particle::doPrint(QDebug stream) const {
    stream <<   "  global ID: "  <<  globalID
           <<   "  id: "         <<  id
           <<   "\tlocation: "   <<  (location ? *(location) : QVector3D(-1.0, -1.0, -1.0))
           <<   "\tsprings: "    <<  springs;
}

int Particle::getGlobalID() const
{
    return globalID;
}

float Particle::energy()
{
    float energy = 0;
    for(auto spring:springs)
    {
        energy += spring.getConstant() * (location->distanceToPoint(spring->getOtherParticle(this)->getLocation()) );
    }
}

void Particle::clear()
{
    Particle::nextGlobalID = 0;
}

void Particle::setLocation(QVector3D *value)
{
    location = value;
}

void Particle::setLocation(float x, float y, float z)
{
    location->setX(x);
    location->setY(y);
    location->setZ(z);
}

QVector<Spring *> Particle::getSprings() const
{
    return springs;
}

int Particle::getId() const
{
    return id;
}

QDebug operator<<(QDebug stream, const Particle &particle){
    particle.doPrint(stream);
    return stream;
}

QDebug operator<<(QDebug stream, Particle *particle){
    particle->doPrint(stream);
    return stream;
}
