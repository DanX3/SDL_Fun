#ifndef PARTICLE_H
#define PARTICLE_H


#include "color.h"

struct Particle {
    int x;
    int y;
    int speed_x;
    int speed_y;
    int w;
    int h;
    Color color;
    bool coupled;

    // Particle(int _x, int _y,
    //     int _speed_x, int _speed_y,
    //     int _w, int _h, Color _color):
    //     x(_x),
    //     y(_y),
    //     speed_x(_speed_x),
    //     speed_y(_speed_y),
    //     w(_w),
    //     h(_h),
    //     color(_color) {}
};

#endif
