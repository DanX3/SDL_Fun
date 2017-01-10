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
        particle_p->speed_x = 1 + rand() % MAX_SPEED;
        particle_p->speed_y = 1 + rand() % MAX_SPEED;
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
    int i = 0;
    int length = particles.size();

    while (i < FRAMES) {
            // std::thread first (&ParticleHandler::adjustParticleSpeed, 0, (int)length/2);
            // std::thread second(&ParticleHandler::adjustParticleSpeed, (int)length/2+1, length);
            // std::thread first (adjustParticleSpeed);
            // std::thread second(adjustParticleSpeed);
            // first.join();
            // second.join();
            thread_data parameterFirst;
            parameterFirst.start = 0;
            parameterFirst.end = length/2;

            pthread_create(threads+0, NULL, [this]{adjustParticleSpeed();}, (void*)&parameterFirst);
            // pthread_create(threads+1, NULL, &ParticleHandler::adjustParticleSpeed, length+1, length);
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
    std::cout << "coupled " << 2 * wheels.size() << " particles" << '\n';
}

// void ParticleHandler::adjustParticleSpeed() {
//     for (size_t i = 0; i < particles.size(); i++) {
//         for (size_t j = 0; j < particles.size(); j++) {
//             if (particles[i]->coupled) continue;
// #if 1
//             if (getSquaredDistance(particles[i], particles[j]) < GRAVITY_RADIUS_SQUARED) {
//                 if (particles[i]->color != particles[j]->color &&
//                     particles[j]->coupled == false) {
//                         onCouple(particles[i], particles[j]);
//                 }
//             }
// #endif
//         }
//     }
// }

void *ParticleHandler::adjustParticleSpeed(void *threadArg) {
    //TODO:this is a terrible bottleneck: computing the distance for all the particles
    thread_data *myData = (thread_data*) threadArg;
    for (size_t i = myData->start; i < myData->end; i++) {
        for (size_t j = 0; j < particles.size(); j++) {
            if (particles[i]->coupled) continue;
#if 1
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
