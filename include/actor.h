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
    virtual void getBoundingRectangle(SDL_Rect* rect) {
        rect->x = 1;
        rect->y = 1;
        rect->w = 1;
        rect->h = 1;
    }

    virtual void onKeyboardEvent(SDL_Event* event) { }
    virtual void onMouseEvent(SDL_Event* event) { }
};

#endif
