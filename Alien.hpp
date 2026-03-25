#ifndef ALIEN_H
#define ALIEN_H

#include <stdbool.h>
#include <GL/freeglut.h>
#include "Themepark.hpp"

struct Alien {
    float x;
    float y;
    float z;
    bool FerrisRiding = false;
};

void drawAlien(Alien*);

#endif