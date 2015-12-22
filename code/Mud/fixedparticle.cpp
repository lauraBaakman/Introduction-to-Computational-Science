#include "fixedparticle.h"

int FixedParticle::nextId = 0;

FixedParticle::FixedParticle(QVector3D* location):
    Particle(location)
{
    id = nextId++;
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

QDebug FixedParticle::doPrint(QDebug stream) const {
    //    return operator<<(stream, this);
        //TODO: actually print the particle
    return stream << "fixedParticle";
}

bool FixedParticle::isFixed() const{
    return true;
}

void FixedParticle::clear()
{
    FixedParticle::nextId = 0;
}
