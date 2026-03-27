#ifndef FERRISWHEEL_H
#define FERRISWHEEL_H

#include <iostream>
#include <fstream>
#include <GL/freeglut.h>
#include <cmath>

#include "vec.hpp"
#include "Alien.hpp"

extern float wheel_angle;
struct Alien;

void loadWheel(void);
void drawWheel(bool shadow);
void drawSupport(void);
void drawSeats(void);

#endif