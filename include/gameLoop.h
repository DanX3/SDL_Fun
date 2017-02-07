#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <SDL.h>
#include <vector>
#include <math.h>
#include "actor.h"
#include "particleHandler.h"
#include "accelCube.h"
#include "actorProperties.h"

class GameLoop {
private:
    SDL_Window* window;
    SDL_Renderer *renderer;
    const static int WINDOW_W = 1600;
    const static int WINDOW_H = 800;
    std::vector<Actor*> actors;
    bool quit;
    SDL_Event event;
    const SDL_Color clearColor = {60, 60, 60, 255};

    void callOnUpdate();
    void callOnDraw();
    void handleEvents();

    const int FPS = 60;
    const float tickStep = 1000.0f / FPS;
public:
    GameLoop(std::string, size_t windowWidth = 800, size_t windowHeight = 600);
    int loop();
    void addActor(Actor*, ActorProperties);
    SDL_Renderer* getRenderer();
    SDL_Window* getWindow();
    void play();
    ~GameLoop();
};

#endif
