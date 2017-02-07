#ifndef ACCELCUBE_H
#define ACCELCUBE_H
#include <SDL.h>
#include "XandY.h"
#include "actor.h"
#include <iostream>

class AcceleratedCube : public Actor {
private:
    SDL_Rect rectangle;
    const float gravity = .1f;
    float verticalSpeed;
    int windowHeight, windowWidth;
protected:
public:
    AcceleratedCube(SDL_Renderer*, SDL_Window*, int, int, int, int);

    void onUpdate();
    void onDraw();
    void onQuit();

    void onKeyboardEvent(SDL_Event* event);
    void onMouseEvent(SDL_Event* event);

    void getBoundingRectangle(SDL_Rect*);
};

#endif 

