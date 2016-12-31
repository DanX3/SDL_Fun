#ifndef PARTICLE_HANDLER_H
#define PARTICLE_HANDLER_H
#include <vector>
#include <string>
#include <iostream>
#include <SDL.h>
#include "actor.h"

class ParticleHandler : public Actor {
private:
    const static int NPARTICLES = 20;
    const static int GRAVITY_RADIUS = 50;
    const static int MAX_SPEED = 7;
    int WINDOW_W, WINDOW_H;

    struct Position {
        int x;
        int y;
    };

    typedef Position XandY;

    enum Color {
        RED, BLUE
    };

    struct Particle {
        int x;
        int y;
        int speed_x;
        int speed_y;
        int w;
        int h;
        Color color;
        bool coupled;

        // Particle(int _x, int _y,
        //     int _speed_x, int _speed_y,
        //     int _w, int _h, Color _color):
        //     x(_x),
        //     y(_y),
        //     speed_x(_speed_x),
        //     speed_y(_speed_y),
        //     w(_w),
        //     h(_h),
        //     color(_color) {}
    };

    std::vector<Particle*> particles;
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
