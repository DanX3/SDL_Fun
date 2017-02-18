#ifndef ACCELCUBE_H
#define ACCELCUBE_H
#include <SDL.h>
#include "XandY.h"
#include "actor.h"
#include <iostream>
#include <math.h>

class AcceleratedCube : public Actor {
private:
    SDL_Rect rectangle;
    const float GRAVITY = 3000.0f;
    const float BOUNCE_TRESHOLD = 600.0f;
    float verticalSpeed;
    bool touchesFloor;
    int windowWidth, windowHeight;

    void jump();
    void fall(unsigned int);
    void bounce(int);
    float x, y;
    float totalEnergy;
    SDL_Color rectColor;
    int colorAdditions[3]={1,1,1};
    const SDL_Color defaultColor={114, 174, 80, 255};
protected:
public:
    AcceleratedCube(SDL_Renderer*, SDL_Window*, SDL_Rect*, SDL_Color* = nullptr);

    void onCollide(Actor*);
    void onUpdate(unsigned int);
    void onDraw();
    void onQuit();

    void onKeyboardEvent(SDL_Event* event);
    void onMouseEvent(SDL_Event* event);

    void getBoundingRectangle(SDL_Rect*);
};

#endif 

