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

    bool isFixed() const;

    void addSpring(Spring *const spring);

    friend QDebug operator<<(QDebug stream, const Particle &particle);

    static void clear();

    QVector<Spring *> getSprings() const;

private:
    QVector3D *location;
    // Force?
    QVector<Spring*> springs;
    bool fixed;
    int id;

    static int nextId;
};
#endif // PARTICLE_H
