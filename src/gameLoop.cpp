#include "gameLoop.h"

GameLoop::GameLoop(std::string title, size_t windowWidth, size_t windowHeight) {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(title.c_str(),
        300, 300,
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

void GameLoop::play() { 
    std::cout << "actorsWithMouseInteraction: "
        << actorsWithMouseInteraction.size() << '\n';
    loop();
}

void GameLoop::addActor(Actor* actor, ActorProperties props) {
    actors.push_back(actor);
    if (props.needMouseEvents()){
        actorsWithMouseInteraction.push_back(actor);
    }
    if (props.needKeyboardEvents()) {
        actorsWithKeyboardInteraction.push_back(actor);
    }
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
    if (event.type == SDL_KEYDOWN) {
        switch(event.key.keysym.sym) {
            case SDLK_UP:
                std::cout << "UP" << '\n';
                break;
            case SDLK_DOWN:
                std::cout << "DOWN" << '\n';
                break;
        }
    }
    if (event.type == SDL_MOUSEMOTION) {
        //I will have a lot of objects on the screen
        //Probably is better the collision here, in the main loop
        //It's true that the collision position depends on the state of the objects

        //Every actor should implement a getBoundingRectangle
        //and a more detailed triangulation of the collision area, for performance
        int x, y;
        SDL_GetMouseState(&x, &y);
        SDL_Point point = {x, y};
        SDL_Rect rect;
        for (Actor* current: actorsWithMouseInteraction) {
            
            //std::cout << "Before calling getBoundingRectangle" << '\n';
            current->getBoundingRectangle(&rect);
            //std::cout << "After calling getBoundingRectangle" << '\n';
            
            if ( SDL_PointInRect(&point, &rect) == SDL_TRUE) {
                current->onMouseEvent(&event);  
            }
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

    for (int i=0; i<700; i+=150) {
        gameLoop.addActor(new AcceleratedCube(renderer, window, i, 50, 100, 100),
            ActorProperties(true, true));
    }

    gameLoop.play();
    return 0;

}
