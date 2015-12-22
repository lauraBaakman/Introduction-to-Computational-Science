#ifndef FIXEDPARTICLE_H
#define FIXEDPARTICLE_H

#include "particle.h"

class FixedParticle : public Particle
{
public:
    FixedParticle(QVector3D* location);

    ~FixedParticle();

    friend QDebug operator<<(QDebug stream, const FixedParticle &particle);
    friend QDebug operator<<(QDebug stream, FixedParticle *particle);

    static void clear();

    bool isFixed() const;

protected:
    virtual void doPrint(QDebug stream) const;

private:
    static int nextIdF;
};

#endif // FIXEDPARTICLE_H
