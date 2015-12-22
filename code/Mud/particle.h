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
    Particle(QVector3D *location = nullptr, bool fixed = false);

    int getId() const;

    QVector3D *getLocation() const;
    void setLocation(QVector3D *value);

    virtual bool isFixed() const;

    void addSpring(Spring *const spring);

    QVector<Spring *> getSprings() const;

protected:
    QVector3D *location;
    QVector<Spring*> springs;
    int id;
};
#endif // PARTICLE_H
