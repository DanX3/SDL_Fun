#include "particleWheel.h"

ParticleWheel::ParticleWheel(Particle *a, Particle *b) :
    first(a),
    second(b) {
        degreeF = 0.0;
        tempCounter = 0;
        circleCenter = getCircleCenter();
        radius = (a->x - b->x) / 2;
        XandY currentPosition;
        currentPosition.x = a->x;
        currentPosition.y = a->y;
        setDegreeFromPosition(&currentPosition);
    }

void ParticleWheel::setDegreeFromPosition(XandY *position) {
    //The tangent is vertical, so degree = PI/2 or 3/2*PI
    if (position->x == circleCenter.x) {
        if (position->y > circleCenter.y)
            degreeFirst = 90;
            degreeSecond = 270;
    }

    double degree = atan((double)(position->y - circleCenter.y) /
        (double)(position->x - circleCenter.x));
    degree = degree * 180 / 3.1415;
    if (position->x < circleCenter.x)
        degree += 180;
    degreeFirst = degree;
    degreeSecond = degree + 180;
}

XandY ParticleWheel::getCircleCenter() {
    XandY midPoint;
    midPoint.x = (first->x + second->x + first->w) / 2;
    midPoint.y = (first->y + second->y + first->h) / 2;
    return midPoint;
}

void ParticleWheel::onInit() {}

void ParticleWheel::onDraw() {
    first->x  = circleCenter.x + cos(3.1415 / 180 * degreeFirst)  * 40;
    first->y  = circleCenter.y + sin(3.1415 / 180 * degreeFirst)  * 40;
    second->x = circleCenter.x + cos(3.1415 / 180 * degreeSecond) * 40;
    second->y = circleCenter.y + sin(3.1415 / 180 * degreeSecond) * 40;
    degreeFirst  += 5;
    degreeSecond += 5;
}

void ParticleWheel::onQuit() {}
