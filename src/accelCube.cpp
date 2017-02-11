#include "accelCube.h"

AcceleratedCube::AcceleratedCube(
    SDL_Renderer* r, SDL_Window* window, int x, int y, int w, int h)
    : Actor(r, window) {
        rectangle.x = x;
        rectangle.y = y;
        rectangle.w = w;
        rectangle.h = h;
        verticalSpeed = 0;
}

AcceleratedCube::AcceleratedCube(SDL_Renderer* r, SDL_Window* w, SDL_Rect* rect)
    : Actor(r, w) {
        rectangle.x = rect->x;
        rectangle.y = rect->y;
        rectangle.w = rect->w;
        rectangle.h = rect->h;
        x = rectangle.x;
        y = rectangle.y;
        SDL_GetWindowSize(w, &windowWidth, &windowHeight);
        totalEnergy = (windowHeight - rectangle.y) * 2;
        verticalSpeed = 0;
        rectColor.r = 114;
        rectColor.g = 174;
        rectColor.b = 80;
        rectColor.a = 255;
    }

void AcceleratedCube::jump() {
    totalEnergy += 1000.0f;
    verticalSpeed -= totalEnergy;

    //change color
    const int diff = 40;
    rectColor.r = (rectColor.r + rectangle.x) % 255;
    //rectColor.g += (rand() % 2 ? -diff : diff);
    //rectColor.b += (rand() % 2 ? -diff : diff);
}

void AcceleratedCube::onUpdate(Uint32 deltaTime) {
    //if the cube can fall 
    //or if it can go up
    int tempY =rectangle.y;
    if (rectangle.h + rectangle.y < windowHeight or verticalSpeed < 0) {
        verticalSpeed += (GRAVITY * deltaTime / 1000.0f);
        y += verticalSpeed * deltaTime / 1000.0f;
        rectangle.y = round(y);
    } else {
    //if it reached the ground
        touchesFloor = true;
        rectangle.y = windowHeight - rectangle.h;
        if (totalEnergy > BOUNCE_TRESHHOLD) {
            totalEnergy /= 1.5f;
        } else {
            totalEnergy = 0;
        }
        verticalSpeed = -totalEnergy;
    }

    if (rectangle.h + rectangle.y < windowHeight) {
        touchesFloor = false;
    }
}

void AcceleratedCube::onDraw() { 
    SDL_SetRenderDrawColor(renderer,  rectColor.r, rectColor.g, rectColor.b, rectColor.a);
    SDL_RenderFillRect(renderer, &rectangle);
}

void AcceleratedCube::onQuit() { }

void AcceleratedCube::getBoundingRectangle(SDL_Rect* rect) {
    rect->x = rectangle.x;
    rect->y = rectangle.y;
    rect->w = rectangle.w;
    rect->h = rectangle.h;
}

void AcceleratedCube::onKeyboardEvent(SDL_Event* event) {
    if (touchesFloor) {
        jump();
    }
}

void AcceleratedCube::onMouseEvent(SDL_Event* event) {
    if (touchesFloor) {
        jump();
    }
}
