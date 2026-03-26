#include "Iceskate.hpp"
#include <math.h>
#include <climits>
#include <list>
#include "loadBMP.h"

GLUquadric *q;		//Quadric object (required for drawing a cylinder)
GLuint txId1;		
int tick = 0;		

struct particle	{	//A particle 
	int t;			//Life time  (0 - 200)
	float col;		//Color  (0 - 1)
	float size;		//Size   (5 - 25)
	float pos[3];	//Position
	float vel[3];	//Velocity
};

list<particle> parList;	//List of particles

static float icetime;
static int scale = 10;
static float speed = 0.005;

Alien iceAlien = {0, 0, 0, false, false, false, false};

//Sweepsurface init
#define NUM_SEGMENTS 20
float radius = 30;
float thickness = 5;


void drawRink(void)
{
	glColor4f(0.5, .9, 1, 1.0);
	glNormal3f(0.0, 1.0, 0.0);

	glBegin(GL_QUADS);
	for(int i = -30; i < 30; i++)	{
		for(int j = 10;  j < 60; j++) {
			glVertex3f(i, 0, j);
			glVertex3f(i, 0, j+1);
			glVertex3f(i+1, 0, j+1);
			glVertex3f(i+1, 0, j);
		}
	}
	glEnd();


}

void drawRinkWalls(bool shadow)
{
	//Sweepsurface Semicircle
	if (!shadow) {glColor4f(.5, .5, .5, 1.0);}


glPushMatrix();
	glTranslatef(0,0,60);
		
	glBegin(GL_QUAD_STRIP);
	for (int i = 0; i <= NUM_SEGMENTS; i++) {
		float theta = 3.14159 * i / NUM_SEGMENTS; 

		glNormal3f(cos(theta), sin(theta), 0);
		glVertex3f(radius * cos(theta), radius * sin(theta), 0);
		glVertex3f(radius * cos(theta), radius * sin(theta), thickness);
	}
	glEnd();

//Sweepsurface Semicircle Face

//Front face
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0, 0, -1);
	glVertex3f(0., 0., 0.);
	for (int i = 0; i <= NUM_SEGMENTS; i++) {
		float theta = 3.14159 * i / NUM_SEGMENTS;

		glVertex3f(radius * cos(theta), radius * sin(theta), 0);
	}
	glEnd();

//Back Face
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0, 0, 1);
	glVertex3f(0, 0, thickness);
	for (int i = 0; i <= NUM_SEGMENTS; i++) {
		float theta = 3.14159 * i / NUM_SEGMENTS;

		glVertex3f(radius * cos(theta), radius * sin(theta), thickness);
	}
	glEnd();

glPopMatrix();
}

void rinkAni(void)
{
    icetime++;
	if (icetime == INT_MAX) icetime = 0;
	tick++;
	if (tick == INT_MAX) tick = 0;

}

void rinkMain(bool shadow)
{
	drawRinkWalls(shadow);

	drawRink();

    float t = icetime * speed;

    float x = scale * (1+0.3*cos(4*t)+0.2*sin(7*t))*cos(t);
    float y = 0.8;
    float z = scale * (1+0.3*cos(4*t)+0.2*sin(7*t))*sin(t) + 35;

    iceAlien.x = x;
    iceAlien.y = y;
    iceAlien.z = z;

    glPushMatrix(); 
        drawAlien(&iceAlien, shadow);
    glPopMatrix();
}