#include "utils.h"

SDL_Texture* Utils::createTextureFromPath(std::string imagePath, SDL_Renderer *renderer) {
    SDL_Surface *surface = SDL_LoadBMP(imagePath.c_str());
    if (surface == NULL) {
        std::cerr << "Resource " << imagePath << " not found" << '\n';
        return NULL;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}
