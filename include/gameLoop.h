#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <SDL.h>
#include <vector>
#include <math.h>
#include "actor.h"
#include "particleHandler.h"

class GameLoop {
private:
    SDL_Window* window;
    SDL_Renderer *renderer;
    const static int WINDOW_W = 800;
    const static int WINDOW_H = 600;
    std::vector<Actor*> actors;

public:
    GameLoop(std::string);
    int onInit();
    int onDraw();
    int onQuit();
};

#endif
