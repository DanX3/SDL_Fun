#ifndef PARTICLE_HANDLER_H
#define PARTICLE_HANDLER_H
#include <vector>
#include <SDL.h>
#include "XandY.h"
#include "particle.h"
#include "actor.h"
#include <thread>
#include "utils.h"

class ParticleHandler : public Actor {
private:

    struct thread_data {
        int start;
        int end;
    };

    unsigned int NPARTICLES;
    const static int GRAVITY_RADIUS = 10;
    const static int GRAVITY_RADIUS_SQUARED =
        GRAVITY_RADIUS * GRAVITY_RADIUS;
    const static int MAX_SPEED = 5;
    int WINDOW_W, WINDOW_H;
    static const int NTHREADS = 2;
    pthread_t threads[NTHREADS];

    typedef XandY Position;

    std::vector<Particle*> particles;
    SDL_Texture *bluePoint, *pinkPoint;
    int texWidth, texHeight;
    SDL_Rect texPosition;

    SDL_Texture* createTextureFromPath(std::string imagePath);
    void printParticle(Particle*);
    void moveParticles();
    void moveParticles(int, int);
    void onCouple(Particle*, Particle*);
    // void adjustParticleSpeed();
    //void *adjustParticleSpeed(void*);
    void adjustParticleSpeed(int start, int end);
    int getSquaredDistance(Particle*, Particle*);
    int getDistanceSum(Particle*, Particle*);
    void onUpdate(unsigned int deltaTime);
    void onDraw();
    void onQuit();
public:
    ParticleHandler(SDL_Renderer*, SDL_Window*, int, int);
};



#endif
