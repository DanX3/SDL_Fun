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
    const float GRAVITY = 3000.0f;
    const float BOUNCE_TRESHHOLD = 600.0f;
    float verticalSpeed;
    bool touchesFloor;
    int windowWidth, windowHeight;
    void jump();
    float x, y;
    float totalEnergy;
    SDL_Color rectColor;
protected:
public:
    AcceleratedCube(SDL_Renderer*, SDL_Window*, int, int, int, int);
    AcceleratedCube(SDL_Renderer*, SDL_Window*, SDL_Rect*);

    void onUpdate(unsigned int);
    void onDraw();
    void onQuit();

    void onKeyboardEvent(SDL_Event* event);
    void onMouseEvent(SDL_Event* event);

    void getBoundingRectangle(SDL_Rect*);
};

#endif 

