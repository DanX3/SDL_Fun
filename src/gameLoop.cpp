#include "gameLoop.h"

GameLoop::GameLoop(std::string title) {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(title.c_str(),
        50, 50,
        WINDOW_W, WINDOW_H,
        SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1,
        SDL_RENDERER_ACCELERATED);
    quit = false;

    userImplementation();

    loop();
}

void GameLoop::userImplementation() {
    actors.push_back(new ParticleHandler(renderer, WINDOW_W, WINDOW_H));
}

int GameLoop::loop() {
    while (!quit) {
        SDL_PollEvent(&event);
        for (size_t i = 0; i < actors.size(); i++) {
            actors[i]->onDraw();
        }

        if (event.type == SDL_QUIT) {
            quit = true;
            for (auto actor : actors) {
                actor->onQuit();
            }
        }
    }
    return 0;
}

GameLoop::~GameLoop() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

int main(int argc, char** argv) {
    GameLoop gameLoop("pink and blue");
    return 0;
}
