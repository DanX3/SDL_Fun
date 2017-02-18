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

    virtual void onCollide(Actor*) {}
    virtual void onUpdate(unsigned int deltaTime) = 0;
    virtual void onDraw() = 0;
    virtual void onQuit() = 0;
    virtual void getBoundingRectangle(SDL_Rect *rect) {
        rect = NULL;
    }
    virtual void getCollisionArea() {
        
    }

    virtual void onKeyboardEvent(SDL_Event* event) { }
    virtual void onMouseEvent(SDL_Event* event) { }
};

#endif
