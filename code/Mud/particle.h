#ifndef PARTICLE_H
#define PARTICLE_H

#include <QVector>
#include <QVector3D>
#include <QDebug>

#include "spring.h"

class Spring;

class Particle
{
public:
    Particle(QVector3D *location = nullptr);
    virtual ~Particle();

    int getId() const;

    QVector3D *getLocation() const;
    void setLocation(QVector3D *value);

    void addSpring(Spring *const spring);
    QVector<Spring *> getSprings() const;

    virtual bool isFixed() const = 0;

    friend QDebug operator<<(QDebug stream, const Particle &particle);
    friend QDebug operator<<(QDebug stream, Particle* particle);

    virtual void doPrint(QDebug stream) const;

    int getGlobalID() const;

protected:
    QVector3D *location;
    QVector<Spring*> springs;
    int id;
    int globalID;

private:
    static int nextGlobalID;

};
#endif // PARTICLE_H
