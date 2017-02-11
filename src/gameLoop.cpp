#include "gameLoop.h"

GameLoop::GameLoop(std::string title, size_t windowWidth, size_t windowHeight) {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(title.c_str(),
        300, 300,
        windowWidth, windowHeight,
        SDL_WINDOW_SHOWN );
    renderer = SDL_CreateRenderer(window, -1,
        SDL_RENDERER_ACCELERATED
        | SDL_RENDERER_PRESENTVSYNC
        );
    quit = false;
}

//void GameLoop::userImplementation() {
     //actors.push_back(new ParticleHandler(renderer, WINDOW_W, WINDOW_H));
     //actors.push_back();
//}

void GameLoop::play() {
    std::cout   << "Actors with collision enabled = " 
                << actorsWithCollision.size() << '\n';
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

    switch(props.needCollision()) {
        case ROUGH:
        case DETAILED:
            actorsWithCollision.push_back(actor);
            break;
        case OFF:
        default:
            break;
    }
}

void GameLoop::callOnUpdate(unsigned int deltaTime) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (size_t i = 0; i < actors.size(); i++) {
        actors[i]->onUpdate(deltaTime);
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
    if (!SDL_PollEvent(&event))
        return;
    if (event.type == SDL_QUIT) {
        quit = true;
        for (auto actor : actors) {
            actor->onQuit();
        }
    }
    if (event.type == SDL_KEYDOWN) {
        for (auto current: actorsWithKeyboardInteraction) {
            current->onKeyboardEvent(&event);
        }
    }
    if (event.type == SDL_MOUSEMOTION) {
    //if (false) {
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
    SDL_FlushEvent(SDL_MOUSEMOTION);
}

void GameLoop::collide() {
    if (actorsWithCollision.size() == 0)
        return;

    SDL_Rect rectangle1, rectangle2;
    for (unsigned int i=0; i<actorsWithCollision.size()-1; i++) {
        for (unsigned int j=i+1; j<actorsWithCollision.size(); j++) {
            actorsWithCollision.at(i)->getBoundingRectangle(&rectangle1);
            actorsWithCollision.at(j)->getBoundingRectangle(&rectangle2);

            if (SDL_TRUE == SDL_HasIntersection(&rectangle1, &rectangle2)) {
                std::cout << "Collision detected" << '\n';    
            }
        }
    }
}

int GameLoop::loop() {
    unsigned int startTick, endTick, timeSpentDrawingFrame = tickStep;
    while (!quit) {
        startTick = SDL_GetTicks();

        collide();

        callOnUpdate(timeSpentDrawingFrame);

        callOnDraw();

        handleEvents();

        if (timeSpentDrawingFrame < tickStep) {
            SDL_Delay(tickStep - timeSpentDrawingFrame);
        }
        endTick = SDL_GetTicks();
        timeSpentDrawingFrame = endTick - startTick;
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
#if 1
    GameLoop gameLoop("pink and blue");
    SDL_Renderer* renderer = gameLoop.getRenderer();
    SDL_Window* window = gameLoop.getWindow();
    SDL_Rect* rectangle = new SDL_Rect{5, 5, 30, 30};
    for (int i=0; i<600; i+=100) {
        rectangle->x = i;
        gameLoop.addActor(new AcceleratedCube(renderer, window, rectangle),
            ActorProperties(MOUSE_INPUT | KEYBOARD_INPUT | COLLISION_ROUGH));

    }

    //gameLoop.addActor(new AcceleratedCube(renderer, window, 50, 50, 50, 50),
        //ActorProperties(true, true));

    gameLoop.play();
#endif
    //ActorProperties props(KEYBOARD_INPUT | MOUSE_INPUT | COLLISION_DETAILED);
    return 0;

}
