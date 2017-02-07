#include "gameLoop.h"

GameLoop::GameLoop(std::string title, size_t windowWidth, size_t windowHeight) {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(title.c_str(),
        50, 50,
        windowWidth, windowHeight,
        SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    quit = false;
}

//void GameLoop::userImplementation() {
     //actors.push_back(new ParticleHandler(renderer, WINDOW_W, WINDOW_H));
     //actors.push_back(); 
//}

void GameLoop::play() { loop(); }

void GameLoop::addActor(Actor* actor, ActorProperties props) {
    actors.push_back(actor);
    std::cout << "Added actor with\n" << props << '\n';
}

void GameLoop::callOnUpdate() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (size_t i = 0; i < actors.size(); i++) {
        actors[i]->onUpdate();
    }
}

void GameLoop::callOnDraw() {
    //clear color before drawing
    SDL_SetRenderDrawColor(renderer,
        clearColor.r,
        clearColor.g,
        clearColor.b,
        clearColor.a);
    SDL_RenderClear(renderer);

    for (size_t i = 0; i < actors.size(); i++) {
        actors[i]->onDraw();
    }

    SDL_RenderPresent(renderer);
}

void GameLoop::handleEvents() {
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT) {
        quit = true;
        for (auto actor : actors) {
            actor->onQuit();
        }
    }
    if (event.type = SDL_KEYDOWN) {
        switch(event.key.keysym.sym) {
            case SDLK_UP:
                std::cout << "UP" << '\n';
                break;
            case SDLK_DOWN:
                std::cout << "DOWN" << '\n';
                break;
        }
    }
}

int GameLoop::loop() {
    while (!quit) {
        Uint32 startTick = SDL_GetTicks();
        callOnUpdate();

        callOnDraw();

        handleEvents();

        Uint32 endTick = SDL_GetTicks();
        Uint32 timeSpentDrawingFrame = endTick - startTick;
        if (timeSpentDrawingFrame < tickStep) {
            SDL_Delay(tickStep - timeSpentDrawingFrame);
        }
    }
    return 0;
}

SDL_Renderer* GameLoop::getRenderer() { return renderer; }
SDL_Window* GameLoop::getWindow() { return window; }

GameLoop::~GameLoop() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

int main(int argc, char** argv) {
    GameLoop gameLoop("pink and blue");
    SDL_Renderer* renderer = gameLoop.getRenderer();
    SDL_Window* window = gameLoop.getWindow();
    gameLoop.addActor(new AcceleratedCube(renderer, window, 50, 50, 50, 50),
        ActorProperties(true, false));
    gameLoop.play();

    return 0;
}
