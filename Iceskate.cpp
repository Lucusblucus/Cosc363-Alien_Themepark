#include "Iceskate.hpp"
#include <math.h>
#include <climits>
#include <list>
	

static float icetime;
static int scale = 10;
static float speed = 0.005;

Alien iceAlien = {0, 0, 0, true, false, false, false};

//Sweepsurface init
#define NUM_SEGMENTS 20
float radius = 30;
float thickness = 5;


void drawRink(void)
{
	glColor4f(0.2, .5, 0.7, 1.0);

	float white[4] = {1., 1., 1., 1.};
	glBindTexture(GL_TEXTURE_2D, txId[1]);

	glBegin(GL_QUADS);
	for(int i = -30; i < 30; i++)	{
		for(int j = 10;  j < 60; j++) {

			glNormal3f(0.0, 1.0, 0.0);

			glTexCoord2f(0, 1);
			glVertex3f(i, 0.1, j);
			glTexCoord2f(0, 0);
			glVertex3f(i, 0.1, j+1);
			glTexCoord2f(1, 0);
			glVertex3f(i+1, 0.1, j+1);
			glTexCoord2f(1, 1);
			glVertex3f(i+1, 0.1, j);
		}
	}
	glEnd();

	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void drawRinkWalls(bool shadow)
{
	float spotpos[] = {0, 20, 45, 1};
	float spotdir[] = {0, 0.5f*sin(0.035f*Angle), 1}; //Spotlight dir

	//Sweepsurface Semicircle
	if (!shadow) {glColor4f(.5, .5, .5, 1.0);}

	//Spotlight
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotdir);
	glLightfv(GL_LIGHT1, GL_POSITION, spotpos);

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

//Right and Left wall
	glPushMatrix();
		glTranslatef(-30, 0.5, -25);
		glScalef(1, 1, 50);
		glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(30, 0.5, -25);
		glScalef(1, 1, 50);
		glutSolidCube(1);
	glPopMatrix();

glPopMatrix();
}

void rinkAni(void)
{
    icetime++;
	if (icetime == INT_MAX) icetime = 0;


}

void rinkMain(bool shadow)
{
	drawRinkWalls(shadow);

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