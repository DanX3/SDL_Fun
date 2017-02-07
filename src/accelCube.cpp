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
    //if the cube can fall 
    if (rectangle.h + rectangle.y < windowHeight) {
        verticalSpeed += gravity;
        rectangle.y += verticalSpeed;
    } else {
    //if it reached the ground
        //if it can go up
        if (verticalSpeed < 0) {
            verticalSpeed += gravity;
            rectangle.y += verticalSpeed;
        } else {
            rectangle.y = windowHeight - rectangle.h;
            verticalSpeed = 0;
        }
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
void AcceleratedCube::onMouseEvent(SDL_Event* event) {
    verticalSpeed -= 10.0f;
    //rectangle.y -= 10;
}


void AcceleratedCube::onKeyboardEvent(SDL_Event* event) {
    verticalSpeed -= 10.0f;
}
