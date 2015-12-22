#ifndef FIXEDPARTICLE_H
#define FIXEDPARTICLE_H

#include "particle.h"

class FixedParticle : public Particle
{
public:
    FixedParticle(QVector3D* location);

    ~FixedParticle();

    friend QDebug operator<<(QDebug stream, const FixedParticle &particle);

    static void clear();

    bool isFixed() const;

private:
    static int nextId;

    QDebug doPrint(QDebug stream) const;
};

#endif // FIXEDPARTICLE_H
