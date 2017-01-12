#ifndef PARTICLE_WHEEL_H
#define PARTICLE_WHEEL_H

#include "particle.h"
#include "XandY.h"
#include "actor.h"
#include <math.h>
#include <iostream>

class ParticleWheel : public Actor {
private:
    const static int ROTATION_SPEED = 0.2;
    Particle *first, *second;
    XandY circleCenter;
    XandY getCircleCenter();
    void setDegreeFromPosition(XandY*);
    int degreeFirst, degreeSecond;
    int degree;
    double degreeF;
    int radius;

    const float RAD2DEG = 3.1415 / 180;

    int tempCounter;
public:
    ParticleWheel(Particle*, Particle*);
    void onUpdate();
    void onDraw();
    void onQuit();
};

#endif
