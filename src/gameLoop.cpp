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
    actors.push_back(new ParticleHandler(renderer, 2,2));
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
    SDL_DestroyWindow(window);
    return 0;
}

int main(int argc, char** argv) {
    GameLoop gameLoop("pink and blue");
    gameLoop.onInit();
    gameLoop.onDraw();
    gameLoop.onQuit();
    return 0;
}
