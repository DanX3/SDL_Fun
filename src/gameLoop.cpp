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
    collideFrameSkip = 0;
    actorsSize = 0;
}

//void GameLoop::userImplementation() {
     //actors.push_back(new ParticleHandler(renderer, WINDOW_W, WINDOW_H));
     //actors.push_back();
//}

void GameLoop::play() {
    std::cout   << "Actors with collision enabled = " 
                << actorsWithCollision.size() << '\n';
    std::cout   << "Actors with mouse interaction = " 
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

    switch(props.needCollision()) {
        case ROUGH:
        case DETAILED:
            actorsWithCollision.push_back(actor);
            break;
        case OFF:
        default:
            break;
    }

    actorsSize++;
}

void GameLoop::callOnUpdate(unsigned int deltaTime) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (size_t i = 0; i < actorsSize; i++) {
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

    for (size_t i = 0; i < actorsSize; i++) {
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
    collideFrameSkip = (collideFrameSkip + 1) % collideMaxFrameSkip;

    for (size_t i=collideFrameSkip; i<actorsSize-1; i+=collideMaxFrameSkip) {
        actorsWithCollision.at(i)->getBoundingRectangle(&rectangle1);
        for (size_t j=i+1; j<actorsSize; j++) {
            actorsWithCollision.at(j)->getBoundingRectangle(&rectangle2);
            if (SDL_TRUE == SDL_HasIntersection(&rectangle1, &rectangle2)) {
                Actor *actor1, *actor2;
                actor1 = actorsWithCollision.at(i);
                actor2 = actorsWithCollision.at(j);
                actor1->onCollide(actor2);
                actor2->onCollide(actor1);
                //std::cout << "Collision detected" << '\n';    
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

        time_elapsed += timeSpentDrawingFrame;
        frames_drawn += 1;
        if (time_elapsed >= 1000) {
            std::cout << frames_drawn / (time_elapsed / 1000) << " FPS" << '\n';
            frames_drawn = 0;
            time_elapsed = 0;
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
#if 1
    GameLoop gameLoop("pink and blue");
    SDL_Renderer* renderer = gameLoop.getRenderer();
    SDL_Window* window = gameLoop.getWindow();

    //gameLoop.addActor( new AcceleratedCube(
        //renderer, window, new SDL_Rect{300,0,100,100}, new SDL_Color{244,67,54,255}),
        //ActorProperties(COLLISION_ROUGH));
    //gameLoop.addActor(new AcceleratedCube(
        //renderer, window, new SDL_Rect{300, 500,100,100}),
        //ActorProperties(COLLISION_ROUGH));


    //for (int i=10; i<900; i+=15) {
        //gameLoop.addActor(new AcceleratedCube(renderer, window,
        //new SDL_Rect{i, 50, 10,20}, new SDL_Color{ i % 256, i % 256, i % 256,255}),
            //ActorProperties(MOUSE_INPUT | KEYBOARD_INPUT));
    //}
    
    gameLoop.addActor(new ParticleHandler(renderer, window, 800, 600), ActorProperties(MOUSE_INPUT));

    gameLoop.play();
#endif
    //ActorProperties props(KEYBOARD_INPUT | MOUSE_INPUT | COLLISION_DETAILED);
    return 0;

}
