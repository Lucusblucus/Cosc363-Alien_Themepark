#ifndef ALIEN_H
#define ALIEN_H

#include <stdbool.h>
#include <GL/freeglut.h>
#include "Themepark.hpp"

struct Alien {
    float x;
    float y;
    float z;
    bool rightarmwaving;
    bool leftarmwaving;
    bool FerrisRiding = false;
};

extern float armAngle;

void drawAlien(Alien*);

#endif