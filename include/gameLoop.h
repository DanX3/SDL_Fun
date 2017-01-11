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
    const static int WINDOW_W = 1600;
    const static int WINDOW_H = 800;
    std::vector<Actor*> actors;
    bool quit;
    SDL_Event event;

public:
    GameLoop(std::string);
    int loop();
    void userImplementation();
    ~GameLoop();
};

#endif
