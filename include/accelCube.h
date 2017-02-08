#ifndef ACCELCUBE_H
#define ACCELCUBE_H
#include <SDL.h>
#include "XandY.h"
#include "actor.h"
#include <iostream>
#include <math.h>
#include <iostream>

class AcceleratedCube : public Actor {
private:
    SDL_Rect rectangle;
    const float gravity = 20.0f;
    float verticalSpeed;
    bool touchesFloor;
    int windowWidth, windowHeight;
    void jump();
    float x, y;
protected:
public:
    AcceleratedCube(SDL_Renderer*, SDL_Window*, int, int, int, int);
    AcceleratedCube(SDL_Renderer*, SDL_Window*, SDL_Rect*);

    void onUpdate(Uint32);
    void onDraw();
    void onQuit();

    void onKeyboardEvent(SDL_Event* event);

    void getBoundingRectangle(SDL_Rect*);
};

#endif 

