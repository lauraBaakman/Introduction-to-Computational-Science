#include "freeparticle.h"

int FreeParticle::nextIdP = 0;

FreeParticle::FreeParticle(QVector3D* location):
    Particle(location)
{
    id = nextIdP++;
}

//Copy constructor
FreeParticle::FreeParticle(QVector3D *location, FreeParticle inputParticle):
    Particle(location)
{
    //Constructor body
    id = inputParticle.id;
    springs = inputParticle.springs;
}

FreeParticle::~FreeParticle(){
    //destructor body
    //qDebug() << "FreeParticle destructor";
}

QDebug operator<<(QDebug stream, const FreeParticle &particle)
{
    stream << &endl
           << "\tFreeParticle ["
           << "  id: "         <<  particle.id
           << "\tlocation: "   <<  (particle.location ? *(particle.location) : QVector3D(-1.0, -1.0, -1.0))
           << "\tsprings: "    <<  particle.springs
           << "]";
    return stream;
}

QDebug operator <<(QDebug stream, FreeParticle* particle){
    stream << *particle;
    return stream;
}

void FreeParticle::doPrint(QDebug stream) const {
    stream  << &endl << "\tFreeParticle [";
    Particle::doPrint(stream);
    stream << "]";
}

bool FreeParticle::isFixed() const{
    return false;
}

void FreeParticle::clear(){
    FreeParticle::nextIdP = 0;
}
