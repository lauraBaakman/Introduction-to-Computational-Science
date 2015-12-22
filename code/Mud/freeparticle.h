#ifndef FREEPARTICLE_H
#define FREEPARTICLE_H

#include "particle.h"

class FreeParticle : public Particle
{
public:
    FreeParticle(QVector3D* location);

    friend QDebug operator<<(QDebug stream, const FreeParticle &particle);

    static void clear();

private:
    static int nextId;
};

#endif // FREEPARTICLE_H
