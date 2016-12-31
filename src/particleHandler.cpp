#include "particleHandler.h"

ParticleHandler::ParticleHandler(SDL_Renderer* r, int windowWidth, int windowHeight) {
    WINDOW_W = windowWidth;
    WINDOW_H = windowHeight;
    renderer = r;
}

void ParticleHandler::renderParticles() {
    int i = 0;
    SDL_SetRenderDrawColor(renderer, 30, 30, 80, 255);
    SDL_RenderClear(renderer);
    int texWidth, texHeight;
    SDL_QueryTexture(pinkPoint, NULL, NULL, &texWidth, &texHeight);
    SDL_Rect texPosition;
    texPosition.w = texWidth;
    texPosition.h = texHeight;
    while (i < NPARTICLES) {
        texPosition.x = particles[i]->x;
        texPosition.y = particles[i]->y;
        SDL_RenderCopy(renderer,
            (particles[i]->color == BLUE ? bluePoint : pinkPoint)
            , NULL, &texPosition);
        i++;
    }
    SDL_RenderPresent(renderer);
}

void ParticleHandler::onInit() {
    //create particle data structures
    pinkPoint = createTextureFromPath("res/pinkpoint.bmp");
    bluePoint = createTextureFromPath("res/bluepoint.bmp");
    int texWidth, texHeight;
    SDL_QueryTexture(pinkPoint, NULL, NULL, &texWidth, &texHeight);
    srand(time(NULL));
    for (size_t i = 0; i < NPARTICLES; i++) {
        Particle *particle_p = new Particle;
        particle_p->x = rand() % (WINDOW_W - texWidth);
        particle_p->y = rand() % (WINDOW_H - texHeight);
        particle_p->speed_x = rand() % MAX_SPEED;
        particle_p->speed_y = rand() % MAX_SPEED;
        particle_p->w = texWidth;
        particle_p->h = texHeight;
        particle_p->color = (i % 2 == 0 ? RED : BLUE);
        particle_p->coupled = false;
        particles.push_back(particle_p);
    }

    std::cout << "created " << particles.size() << " particles" << '\n';

    renderParticles();
}

void ParticleHandler::printParticle(Particle *p) {
    std::cout << "Position" << '\n'
        << "\t" << p->x << ", " << p->y << '\n'
        << "Speed" << '\n'
        << "\t" << p->speed_x << ", " << p->speed_y << '\n'
        << "Dimension" << '\n'
        << "\t" << p->w << ", " << p->h << "\n\n";
}

void ParticleHandler::onDraw() {
    const int frames = 60 * 7;
    int i = 0;
    while (i < frames) {
        adjustParticleSpeed();
        moveParticles();
        for (size_t j = 0; j < wheels.size(); j++) {
            wheels[j]->onDraw();
        }
        renderParticles();
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

void ParticleHandler::moveParticles() {
    for (size_t i = 0; i < particles.size(); i++) {
        particles[i]->x += particles[i]->speed_x;
        particles[i]->y += particles[i]->speed_y;
        if (particles[i]->x < 0) {
            particles[i]->x *= -1;
            particles[i]->speed_x *= -1;
        }
        if (particles[i]->y < 0) {
            particles[i]->y *= -1;
            particles[i]->speed_y *= -1;
        }
        int validX = WINDOW_W - particles[i]->w;
        int validY = WINDOW_H - particles[i]->h;
        if (particles[i]->x  > validX) {
            particles[i]->x -= particles[i]->x - validX;
            particles[i]->speed_x *= -1;
        }
        if (particles[i]->y > validY) {
            particles[i]->y -= particles[i]->y - validY;
            particles[i]->speed_y *= -1;
        }
    }
}

SDL_Texture* ParticleHandler::createTextureFromPath(std::string imagePath) {
    SDL_Surface *surface = SDL_LoadBMP(imagePath.c_str());
    if (surface == NULL) {
        std::cerr << "Resource " << imagePath << " not found" << '\n';
        return NULL;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    std::cout << "imagePath:" << texture << '\n';
    SDL_FreeSurface(surface);
    return texture;
}

void ParticleHandler::adjustParticleSpeed() {
    XandY affectedSpeed;
    for (size_t i = 0; i < particles.size(); i++) {
        affectedSpeed.x = 0;
        affectedSpeed.y = 0;
        int affectedParticles = 0;
        for (size_t j = 0; j < particles.size(); j++) {
            if (particles[i]->coupled) continue;

            int squaredDistance = getSquaredDistance(particles[i], particles[j]);
            bool isAffected = squaredDistance < GRAVITY_RADIUS*GRAVITY_RADIUS;
            if (isAffected) {
                if (particles[i]->color != particles[j]->color &&
                    particles[j]->coupled == false) {
                    particles[i]->speed_x = 0;
                    particles[i]->speed_y = 0;
                    particles[j]->speed_x = 0;
                    particles[j]->speed_y = 0;
                    particles[i]->coupled = true;
                    particles[j]->coupled = true;
                    ParticleWheel *wheel =
                        new ParticleWheel(particles[i], particles[j]);
                    wheels.push_back(wheel);
                }
            }
        }
    }
}
