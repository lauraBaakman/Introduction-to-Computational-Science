#include "freeparticle.h"

int FreeParticle::nextId = 0;

FreeParticle::FreeParticle(QVector3D* location):
    Particle(location)
{
    id = nextId++;
}


FreeParticle::~FreeParticle(){
    //destructor body
    qDebug() << "FreeParticle destructor";
}

QDebug operator<<(QDebug stream, const Particle &particle)
{
    stream << &endl
           << "\tFreeParticle ["
           << "  id: "         <<  particle.id
           << "\tlocation: "   <<  (particle.location ? *(particle.location) : QVector3D(-1.0, -1.0, -1.0))
           << "\tsprings: "    <<  particle.springs
           << "]";
    return stream;
}

QDebug FreeParticle::doPrint(QDebug stream) const {
    //    return operator<<(stream, this);
    //TODO: actually print the particle
    return stream << "freeParticle";
}


bool FreeParticle::isFixed() const{
    return false;
}

void FreeParticle::clear(){
    FreeParticle::nextId = 0;
}
