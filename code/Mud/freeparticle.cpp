#include "freeparticle.h"

int FreeParticle::nextId = 0;

FreeParticle::FreeParticle(QVector3D* location):
    Particle(location)
{
    id = nextId++;
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

bool FreeParticle::isFixed(){
    return false;
}

void FreeParticle::clear(){
    FreeParticle::nextId = 0;
}
