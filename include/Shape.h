#ifndef SHAPE_H
#define SHAPE_H

#include <SDL2/SDL.h>
#include "World.h"

// Classe abstrata (interface para todas as figuras)
class Shape {
public:
    virtual ~Shape() {}
    virtual void draw(SDL_Surface* surface, World mundo) {
    }

    virtual void draw(SDL_Surface* surface) {
    }
};

#endif

