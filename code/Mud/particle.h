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

    int getId() const;

    QVector3D *getLocation() const;
    void setLocation(QVector3D *value);

    void addSpring(Spring *const spring);
    QVector<Spring *> getSprings() const;

    virtual bool isFixed() const = 0;

    friend QDebug operator<<(QDebug stream, const Particle &particle);

protected:
    QVector3D *location;
    QVector<Spring*> springs;
    int id;

private:
    virtual QDebug doPrint(QDebug stream) const;
};
#endif // PARTICLE_H
