#include <SDL.h>
#include "XandY.h"
#include "particle.h"
#include "actor.h"
#include <thread>
#include "particleWheel.h"
#include "utils.h"


class AcceleratedCube : public Actor {
private:
    SDL_Rect rectangle;
    const float gravity = .2f;
    float verticalSpeed;
    int windowHeight, windowWidth;
protected:
public:
    AcceleratedCube(SDL_Renderer*, SDL_Window*, int, int, int, int);

    void onUpdate();
    void onDraw();
    void onQuit();
};
