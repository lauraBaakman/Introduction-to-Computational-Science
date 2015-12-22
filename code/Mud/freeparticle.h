#ifndef FREEPARTICLE_H
#define FREEPARTICLE_H

#include "particle.h"

class FreeParticle : public Particle
{
public:
    FreeParticle(QVector3D* location);
    ~FreeParticle();

//    friend QDebug operator<<(QDebug stream, const FreeParticle &particle);

    static void clear();

    bool isFixed() const;

private:
    static int nextIdP;

    QDebug doPrint(QDebug stream) const;
};

#endif // FREEPARTICLE_H
