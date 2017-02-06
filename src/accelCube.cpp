#include "accelCube.h"

AcceleratedCube::AcceleratedCube(
    SDL_Renderer* r, SDL_Window* window, int x, int y, int w, int h)
    : Actor(r, window) {
        rectangle.x = x;
        rectangle.y = y;
        rectangle.w = w;
        rectangle.h = h;
        SDL_GetWindowSize(window, &windowWidth, &windowHeight);
        verticalSpeed = 0;
}

void AcceleratedCube::onUpdate() {
    if (rectangle.h + rectangle.y < windowHeight) {
        verticalSpeed += gravity;
        rectangle.y += verticalSpeed;
    } else {
        rectangle.y = windowHeight - rectangle.h;
        verticalSpeed = 0;
    }
}
void AcceleratedCube::onDraw() { 
    SDL_SetRenderDrawColor(renderer,  114, 175, 80, 255);
    SDL_RenderFillRect(renderer, &rectangle);
}
void AcceleratedCube::onQuit() { }
