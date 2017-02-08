#ifndef ACTOR_H
#define ACTOR_H

class Actor {
protected:
    SDL_Renderer* renderer;
    SDL_Window* window;
public:
    Actor(SDL_Renderer* r, SDL_Window* w) {
        renderer = r;
        window = w;
    }

    virtual void onUpdate(Uint32 deltaTime) = 0;
    virtual void onDraw() = 0;
    virtual void onQuit() = 0;
    virtual void getBoundingRectangle(SDL_Rect* rect) {
        rect->x = 0;
        rect->y = 0;
        rect->w = 0;
        rect->h = 0;
    }

    virtual void onKeyboardEvent(SDL_Event* event) { }
    virtual void onMouseEvent(SDL_Event* event) { }
};

#endif
