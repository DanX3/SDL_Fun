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
        std::cout << windowWidth << 'x' << windowHeight << '\n';

        verticalSpeed = 0;
    }

void AcceleratedCube::jump() {
    verticalSpeed -= 1000.f;
}

void AcceleratedCube::onUpdate(Uint32 deltaTime) {
    //if the cube can fall 
    //or if it can go up
    int tempY =rectangle.y;
    if (rectangle.h + rectangle.y < windowHeight or verticalSpeed < 0) {
        verticalSpeed += gravity;
        y += verticalSpeed * deltaTime / 1000.0f;
        rectangle.y = round(y);
        std::cout << deltaTime << ')' << rectangle.y - tempY << '\n';
    } else {
    //if it reached the ground
        touchesFloor = true;
        rectangle.y = windowHeight - rectangle.h;
        verticalSpeed = 0;
    }

    if (rectangle.h + rectangle.y < windowHeight) {
        touchesFloor = false;
    }
}
void AcceleratedCube::onDraw() { 
    SDL_SetRenderDrawColor(renderer,  114, 175, 80, 255);
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
