#include "Animation.hpp"
#include "Alien.hpp"

int frame = 0;

FerrisState ferrisstate = RUNNING;

void aniMain(Alien* alien)
{
    frame++;
    armAngle++;

    switch (ferrisstate)
    {
        case RUNNING:
            wheel_angle += 0.3;
            if (wheel_angle >= 180) { 
                ferrisstate = LOADING;
                wheel_angle = 0.1;
                frame = 0;
            }
            break;
        
        case LOADING:
            alien->z -= 0.025;

            if (frame >= 120) { //Wait Approx 2 secs
                wheel_angle = 0.1;
                ferrisstate = RIDING;
            }
            break;

        case RIDING:
            alien ->FerrisRiding = true;
            alien ->leftarmwaving = true;
            alien ->rightarmwaving = true;
            wheel_angle += 0.3;
            if (wheel_angle >= 360) {
                wheel_angle = 0.1;
                frame = 0;
                ferrisstate = UNLOADING;
            }
            break;

        case UNLOADING:
            alien -> FerrisRiding = false;
            alien ->leftarmwaving = false;
            alien ->rightarmwaving = false;
            alien -> z += 0.025;
            if (frame >= 120) { //Wait Approx 2 secs
                ferrisstate = RUNNING;
            }
            break;
    }
}