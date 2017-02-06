#include "particleHandler.h"

ParticleHandler::ParticleHandler(SDL_Renderer* r, SDL_Window* w, int windowWidth, int windowHeight)
    : Actor(r, w) {
    WINDOW_W = windowWidth;
    WINDOW_H = windowHeight;
    renderer = r;

    //create particle data structures
    pinkPoint = Utils::createTextureFromPath("res/pinkpoint.bmp", renderer);
    bluePoint = Utils::createTextureFromPath("res/bluepoint.bmp", renderer);
    SDL_QueryTexture(pinkPoint, NULL, NULL, &texWidth, &texHeight);
    texPosition.w = texWidth;
    texPosition.h = texHeight;
    srand(time(NULL));
    for (size_t i = 0; i < NPARTICLES; i++) {
        Particle *particle_p = new Particle;
        particle_p->x = rand() % (WINDOW_W - texWidth);
        particle_p->y = rand() % (WINDOW_H - texHeight);
        particle_p->speed_x = 1 + rand() % (2*MAX_SPEED) - MAX_SPEED;
        particle_p->speed_y = 1 + rand() % (2*MAX_SPEED) - MAX_SPEED;
        particle_p->w = texWidth;
        particle_p->h = texHeight;
        particle_p->color = (i % 2 == 0 ? RED : BLUE);
        particle_p->coupled = false;
        particles.push_back(particle_p);
    }
}

void ParticleHandler::printParticle(Particle *p) {
    std::cout << "Position" << '\n'
        << "\t" << p->x << ", " << p->y << '\n'
        << "Speed" << '\n'
        << "\t" << p->speed_x << ", " << p->speed_y << '\n'
        << "Dimension" << '\n'
        << "\t" << p->w << ", " << p->h << "\n\n";
}

void ParticleHandler::onUpdate() {
    int length = particles.size();
    std::thread first (&ParticleHandler::adjustParticleSpeed, this, 0, length/2);
    std::thread second(&ParticleHandler::adjustParticleSpeed, this, length/2+1, length);
    first.join();
    second.join();
    moveParticles();
}

void ParticleHandler::onDraw() {
    for (size_t j = 0; j < wheels.size(); j++) {
        wheels[j]->onDraw();
    }

    int i = 0;
    for (auto particle : particles) {
        texPosition.x = particle->x;
        texPosition.y = particle->y;
        SDL_RenderCopy(renderer,
            (particle->color == BLUE ? bluePoint : pinkPoint)
            , NULL, &texPosition);
        i++;
    }
}

void ParticleHandler::onQuit() {
    for (size_t i = 0; i < particles.size(); i++) {
        free(particles[i]);
    }

    for (size_t i = 0; i < wheels.size(); i++) {
        free(wheels[i]);
    }

    SDL_DestroyTexture(bluePoint);
    SDL_DestroyTexture(pinkPoint);
}

int ParticleHandler::getSquaredDistance(Particle *first, Particle *second) {
    int deltaX = second->x - first->x;
    int deltaY = second->y - first->y;
    return (deltaX * deltaX) + (deltaY * deltaY);
}

int ParticleHandler::getDistanceSum(Particle* first, Particle* second) {
    return (second->x - first->x) + (second->y + first->y);
}

void ParticleHandler::moveParticles() {
    for (size_t i = 0; i < particles.size(); i++) {
        particles[i]->x += particles[i]->speed_x;
        particles[i]->y += particles[i]->speed_y;
        if ((particles[i]->y < 0) or
            (particles[i]->y > WINDOW_H - particles[i]->h)) {
            particles[i]->speed_y *= -1;
            continue;
        }
        if ((particles[i]->x < 0) or
        (particles[i]->x > WINDOW_W - particles[i]->w)) {
            particles[i]->speed_x *= -1;
        }
    }
}

void ParticleHandler::moveParticles(int start, int end) {
    for (size_t i = start; i < end; i++) {
        particles[i]->x += particles[i]->speed_x;
        particles[i]->y += particles[i]->speed_y;
        if ((particles[i]->y < 0) or
            (particles[i]->y > WINDOW_H - particles[i]->h)) {
            particles[i]->speed_y *= -1;
            continue;
        }
        if ((particles[i]->x < 0) or
        (particles[i]->x > WINDOW_W - particles[i]->w)) {
            particles[i]->speed_x *= -1;
        }
    }
}


void ParticleHandler::onCouple(Particle *first, Particle* second) {
    first ->speed_x = 0;
    second->speed_y = 0;
    first ->speed_x = 0;
    second->speed_y = 0;
    first ->coupled = true;
    second->coupled = true;
    ParticleWheel *wheel =
        new ParticleWheel(first, second);
    wheels.push_back(wheel);
    //std::cout << "coupled " << 2 * wheels.size() << " particles" << '\n';
}

void ParticleHandler::adjustParticleSpeed(int start, int end) {
    //only blue particles compute the distance to the pink ones
    //the outer for cycle through the blue particles
    //the inner for cycle through the pink particles
    for (size_t i = start; i < end; i+=2) {
        for (size_t j = 1; j < particles.size(); j+=2) {
            if (particles[i]->coupled) continue;
#if 0
            if (getDistanceSum(particles[i], particles[j]) < GRAVITY_RADIUS_SQUARED) {
                if (particles[i]->color != particles[j]->color &&
                    particles[j]->coupled == false) {
                        onCouple(particles[i], particles[j]);
                }
            }
#endif
        }
    }
}
