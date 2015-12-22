#ifndef FIXEDPARTICLE_H
#define FIXEDPARTICLE_H

#include "particle.h"

class FixedParticle : public Particle
{
public:
    FixedParticle(QVector3D* location);

    friend QDebug operator<<(QDebug stream, const FixedParticle &particle);

    static void clear();

private:
    static int nextId;
};

#endif // FIXEDPARTICLE_H
