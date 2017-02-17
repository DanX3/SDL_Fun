#include "accelCube.h"

AcceleratedCube::AcceleratedCube(SDL_Renderer* r, SDL_Window* w, SDL_Rect* rect,
    SDL_Color* color)
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
        if (color == nullptr) {
            rectColor = defaultColor;
        } else {
            rectColor = *color;
        }
        rectColor.r = 255;
        rectColor.g = 255;
        rectColor.b = 255;
        //rectColor.a = 255;
}

void AcceleratedCube::onCollide(Actor* actorICollidedWith) {
    if (totalEnergy == 0)
        return;

    SDL_Rect r;
    actorICollidedWith->getBoundingRectangle(&r);
    bounce(windowHeight - r.y);
    //bounce(0);
}

void AcceleratedCube::jump() {
    totalEnergy += 1000.0f;
    verticalSpeed -= totalEnergy;

    //change color
    //const int diff = 40;
    //rectColor.r = (rectColor.r + rectangle.x) % 255;
    //rectColor.g += (rand() % 2 ? -diff : diff);
    //rectColor.b += (rand() % 2 ? -diff : diff);
}

void AcceleratedCube::bounce(int bounceSurfaceHeight) {
        std::cout << "Stopped falling" << '\n';
        std::cout << "totalEnergy =  " << totalEnergy << '\n';
        std::cout << "verticalSpeed =  " << verticalSpeed << '\n';
    touchesFloor = true;
    y = windowHeight - rectangle.h - bounceSurfaceHeight;
    rectangle.y = round(y);
    if (totalEnergy > BOUNCE_TRESHOLD) {
        totalEnergy /= 1.5f;
    } else {
        totalEnergy = 0;
    }
    verticalSpeed = -totalEnergy;
}

void AcceleratedCube::fall(unsigned int deltaTime) {
    verticalSpeed += (GRAVITY * deltaTime / 1000.0f);
    y += verticalSpeed * deltaTime / 1000.0f;
    rectangle.y = round(y);
}

void AcceleratedCube::onUpdate(Uint32 deltaTime) {
    //if the cube can fall 
    //or if it can go up
    if (rectangle.h + rectangle.y < windowHeight or verticalSpeed < 0) {
        fall(deltaTime);
    } else {
        if (totalEnergy > 0)
            bounce(0);
    }

    if (rectangle.h + rectangle.y < windowHeight) {
        touchesFloor = false;
    }

    //changes color by a single step
    if (rand() % 2) {
        int nextValue = rectColor.r + colorAdditions[0];
        if (nextValue == 0 || nextValue >= 255) {
            colorAdditions[0] *=-1;
        }
        rectColor.r += colorAdditions[0];
    }
    
   else if (rand() % 2) {
        int nextValue = rectColor.g + colorAdditions[1];
        if (nextValue == 0 || nextValue >= 255) {
            colorAdditions[1] *=-1;
        }
        rectColor.g += colorAdditions[1];
    }

    else {
        int nextValue = rectColor.b + colorAdditions[2];
        if (nextValue == 0 || nextValue >= 255) {
            colorAdditions[2] *=-1;
        }
        rectColor.b += colorAdditions[2];
    }
}

void AcceleratedCube::onDraw() { 
    SDL_SetRenderDrawColor(renderer,  rectColor.r, rectColor.g, rectColor.b, rectColor.a);
    SDL_RenderFillRect(renderer, &rectangle);
}

void AcceleratedCube::onQuit() { }

void AcceleratedCube::getBoundingRectangle(SDL_Rect* const rect) {
    rect->x = rectangle.x;
    rect->y = rectangle.y;
    rect->w = rectangle.w;
    rect->h = rectangle.h;
    //rect = &rectangle;
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
