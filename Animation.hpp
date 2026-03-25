#ifndef ANIMATION_H
#define ANIMATION_H

#include "Ferriswheel.hpp"

extern int frame; 
struct Alien;

enum FerrisState
{
    RUNNING,
    LOADING,
    RIDING,
    UNLOADING,
};

void aniMain(Alien*);


#endif