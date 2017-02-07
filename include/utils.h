#ifndef UTILS_H
#define UTILS_H

#include <SDL.h>
#include <string>
#include <iostream>


class Utils {
public:
    static SDL_Texture* createTextureFromPath(std::string, SDL_Renderer *);
    static bool pointInRectangle(SDL_Point* p, SDL_Rect* r);
};

#endif
