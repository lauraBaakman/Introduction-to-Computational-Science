#include "fixedparticle.h"

int FixedParticle::nextIdF = 0;

FixedParticle::FixedParticle(QVector3D* location):
    Particle(location)
{
    id = nextIdF++;
}

FixedParticle::~FixedParticle(){
    qDebug() << "FixedParticle destructor";
}

QDebug operator<<(QDebug stream, const FixedParticle &particle)
{
    stream << &endl
           << "\tFixedParticle ["
           << "  id: "         <<  particle.id
           << "\tlocation: "   <<  (particle.location ? *(particle.location) : QVector3D(-1.0, -1.0, -1.0))
           << "\tsprings: "    <<  particle.springs
           << "]";
    return stream;
}

QDebug operator<<(QDebug stream, FixedParticle *particle){
    stream << *particle;
    return stream;
}

void FixedParticle::doPrint(QDebug stream) const{
    stream  << "\tFixedParticle[";
    Particle::doPrint(stream);
    stream << "]" << &endl;
}


bool FixedParticle::isFixed() const{
    return true;
}

void FixedParticle::clear()
{
    FixedParticle::nextIdF = 0;
}
