#ifndef ACTOR_H
#define ACTOR_H

#include "XandY.h"

class Actor {
protected:
    SDL_Renderer* renderer;
    SDL_Window* window;
public:
    Actor(SDL_Renderer* r, SDL_Window* w) :
        renderer(r),
        window(w) { }
    virtual void onUpdate() = 0;
    virtual void onDraw() = 0;
    virtual void onQuit() = 0;
};

#endif
