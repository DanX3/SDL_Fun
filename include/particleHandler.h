#ifndef PARTICLE_HANDLER_H
#define PARTICLE_HANDLER_H
#include <vector>
#include <string>
#include <iostream>
#include <SDL.h>
#include "XandY.h"
#include "particle.h"
#include "actor.h"
#include "particleWheel.h"

class ParticleHandler : public Actor {
private:
    const static int NPARTICLES = 20;
    const static int GRAVITY_RADIUS = 50;
    const static int MAX_SPEED = 7;
    int WINDOW_W, WINDOW_H;

    typedef XandY Position;

    std::vector<Particle*> particles;
    std::vector<ParticleWheel*> wheels;
    SDL_Texture *bluePoint, *pinkPoint;
    SDL_Renderer* renderer;

    SDL_Texture* createTextureFromPath(std::string imagePath);
    void printParticle(Particle*);
    void moveParticles();
    void adjustParticleSpeed();
    int getSquaredDistance(Particle *first, Particle *second);
    void renderParticles();
    void onInit();
    void onDraw();
    void onQuit();
public:
    ParticleHandler(SDL_Renderer*, int, int);
};



#endif
