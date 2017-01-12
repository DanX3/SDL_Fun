#include "gameLoop.h"

GameLoop::GameLoop(std::string title) {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(title.c_str(),
        50, 50,
        WINDOW_W, WINDOW_H,
        SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    quit = false;

    userImplementation();

    loop();
}

void GameLoop::userImplementation() {
    actors.push_back(new ParticleHandler(renderer, WINDOW_W, WINDOW_H));
}

int GameLoop::loop() {
    while (!quit) {
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        for (auto actor: actors) {
            actor->onUpdate();
            actor->onDraw();
        }

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
            SDL_Delay(50);
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
