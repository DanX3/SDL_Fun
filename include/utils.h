#ifndef UTILS_H
#define UTILS_H

#include <SDL.h>
#include <string>
#include <iostream>


class Utils {
public:
    static SDL_Texture* createTextureFromPath(std::string, SDL_Renderer *);
};

#endif
