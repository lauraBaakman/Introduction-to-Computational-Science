#ifndef FREEPARTICLE_H
#define FREEPARTICLE_H

#include "particle.h"

class FreeParticle : public Particle
{
public:
    FreeParticle(QVector3D* location);
    ~FreeParticle();

    friend QDebug operator<<(QDebug stream, const FreeParticle &particle);
    friend QDebug operator<<(QDebug stream, FreeParticle *particle);

    static void clear();

    bool isFixed() const;

protected:
    virtual void doPrint(QDebug stream) const;

private:
    static int nextIdP;
};

#endif // FREEPARTICLE_H
