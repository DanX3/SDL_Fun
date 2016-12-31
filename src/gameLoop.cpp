#include "gameLoop.h"

GameLoop::GameLoop(std::string title) {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(title.c_str(),
        100, 100,
        WINDOW_W, WINDOW_H,
        SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

int GameLoop::onInit() {
    actors.push_back(new ParticleHandler(renderer, WINDOW_W, WINDOW_H));
    for (size_t i = 0; i < actors.size(); i++) {
        actors[i]->onInit();
    }


    return 0;
}

int GameLoop::onDraw() {
    for (size_t i = 0; i < actors.size(); i++) {
        actors[i]->onDraw();
    }
    return 0;
}

int GameLoop::onQuit() {
    SDL_Delay(1000);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    return 0;
}

int main(int argc, char** argv) {
    GameLoop gameLoop("pink and blue");
    gameLoop.onInit();
    std::cout << "onInitExecuted" << '\n';
    gameLoop.onDraw();
    std::cout << "onDrawExecuted" << '\n';
    gameLoop.onQuit();
    return 0;
}
