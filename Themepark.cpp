//  ========================================================================
//  Luke Burling - 46662217
//	COSC363 Assignment 1
//  Alien Themepark
//
//  FILE NAME: Themepark.cpp
//  
//  ========================================================================

#include "Themepark.hpp"
#include "loadTGA.h"
using namespace std;

//-- Globals ---------------------------------------------------------------
float angle=0., look_x=0., look_z=0., eye_x=0., eye_y=5., eye_z=10.;
bool wireframe = false; //Varible to track if wireframe is active
float Angle = 0;

int turndirection=0, movedirection=0, updirection=0;

GLuint txId[2];	//Texture ids

//Init Aliens
Alien alien1 = {0, 2,-2, false, false, false};

//-- Draws a grid of lines on the floor plane ------------------------------
void drawFloor() {
	float white[4] = {1., 1., 1., 1.};
	float black[4] = {0., 0., 0., 1.};
	glColor4f(0., 0.5, 0., 1.0);	
	glNormal3f(0.0, 1.0, 0.0);		//Normal vector of the floor

	glMaterialfv(GL_FRONT, GL_SPECULAR, black); //Only diffuse reflection from floor

	//The floor is made up of several tiny squares on a 400 x 400 grid. Each square has a unit size.
	glBegin(GL_QUADS);
	for(int i = -200; i < 200; i++)	{
		for(int j = -200;  j < 200; j++) {
			glVertex3f(i, 0, j);
			glVertex3f(i, 0, j+1);
			glVertex3f(i+1, 0, j+1);
			glVertex3f(i+1, 0, j);
		}
	}
	glEnd();

	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
}

//-- Texture and Skybox ------------------------------------------

//--------------------------------------------------------------------------
void loadTexture() {
	glGenTextures(2, txId); // Create 2 texture ids

	glBindTexture(GL_TEXTURE_2D, txId[0]);	//Use this texture
	loadTGA("Skybox.tga");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//Set texture parameters
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	
	
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
}

void skyBox(void)
{
	GLUquadricObj* q;
	q = gluNewQuadric();
	glPushMatrix();
	gluQuadricOrientation(q, GLU_INSIDE);
	gluQuadricTexture (q, GL_TRUE);
	glBindTexture(GL_TEXTURE_2D, txId[0]);
	glRotatef(-90., 1.0, 0., 0.0);
	gluSphere(q, 1500, 18, 9);
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
}

//Box for Alien to stand on
void drawBox(bool shadow)
{
	if (!shadow) {glColor4f(0.2, 0.5, 0.5, 1);}
	glTranslatef(0, 0.8, -2);
	glScalef(2, 0.6, 1);
	glutSolidCube(2);
}

//-- Draws the Ferris wheel ----------------
void drawFerris(bool shadow) {
	glTranslatef(0, 18, -5);
	//Supports
	if (!shadow) {glColor4f(0.5, 0.5, 0.5, 1);}	
	drawSupport();

	//Wheel, Seats
	glPushMatrix();
		glRotatef(wheel_angle, 0, 0, 1);

		if (!shadow) {glColor4f(0.5, 0., 0., 1.);}	
		drawWheel();

		if (!shadow) {glColor4f(0, 0, 0.5, 1.);}
		drawSeats();
	glPopMatrix();
}

void movement(void)
{
	//Smooth Movement
	angle += 0.03 * turndirection;
	look_x = eye_x + 10*sin(angle);
	look_z = eye_z - 10*cos(angle);
	eye_x += 0.4*sin(angle) * movedirection;
	eye_z -= 0.4*cos(angle) * movedirection;
	eye_y += 0.5 * updirection;
}

void myTimer(int value) {
	
	aniMain(&alien1);
	rinkAni();
	movement();

	glutPostRedisplay();
	glutTimerFunc(16, myTimer, value);
}

//-- Display: --------------------------------------------------------------
//-- This is the main display module containing function calls for generating
//-- the scene.
void display() {
	float light[4] = {50., 150., 50., 1.};	//light's position
	float shadowMat[16] = {light[1], 0, 0, 0, -light[0], 0, -light[2],-1,
 							0, 0, light[1], 0, 0, 0, 0, light[1]};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(eye_x, eye_y, eye_z, look_x, eye_y, look_z, 0., 1., 0.);
	glLightfv(GL_LIGHT0,GL_POSITION, light);   //Set light position

	glRotatef(angle, 0., 2., 0.);	//Rotate the scene about the y-axis
	glEnable(GL_LIGHTING);	
	skyBox();

	rinkMain(false);

	drawFloor();
	if (!alien1.FerrisRiding) {
		drawAlien(&alien1, false);
	}
	glPushMatrix();
		drawBox(false);	
	glPopMatrix();
	glPushMatrix();
		drawFerris(false);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0, 19, -5);
		glRotatef(wheel_angle, 0, 0, 1);
		if (alien1.FerrisRiding) {drawAlien(&alien1, false);}
	glPopMatrix();

	glDisable(GL_LIGHTING);	

	glColor3f(0.2, 0.2, 0.2);
	glPushMatrix();
		glTranslatef(0., 0.15, 0.);
		glMultMatrixf(shadowMat);
		glPushMatrix();
			drawFerris(true);
		glPopMatrix();
		glPushMatrix();
			drawBox(true);
		glPopMatrix();
		glPushMatrix();
			rinkMain(true);
		glPopMatrix();
		
	glPopMatrix();

	glFlush();
}

//-- Initialize OpenGL parameters ------------------------------------------
void initialize() {
	glClearColor(.5, .5, .5, 1.);	//Background colour
	float white[4]  = {1., 1., 1., 1.};

	glEnable(GL_LIGHTING);			//Enable OpenGL states
	glEnable(GL_LIGHT0);

	//	Define light's diffuse, specular properties
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white);	//Default, only for LIGHT0
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);	//Default, only for LIGHT0
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialf(GL_FRONT, GL_SHININESS, 50);

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_TEXTURE_2D);

	loadTexture();
	loadWheel();
 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70., (float)16/(float)9, 1., 2000.);	//Camera Frustum
}

//-- Special key event callback --------------------------------------------
//-- To enable the use of keys to move about the screen
void special(int key, int x, int y) {
	if		(key == GLUT_KEY_LEFT)  {turndirection = -1;}//Rotate Left
	else if (key == GLUT_KEY_RIGHT) {turndirection =  1;}//Rotate Right

	if   	(key == GLUT_KEY_DOWN) {movedirection = -1;}//Move backward
	else if (key == GLUT_KEY_UP)   {movedirection = 1;} //Move forward

	if		(key == GLUT_KEY_PAGE_UP)   {updirection = 1;} //Move up
	else if (key == GLUT_KEY_PAGE_DOWN) {updirection = -1;}//Move down

	glutPostRedisplay();
}

void specialUp(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT || key == GLUT_KEY_RIGHT) {
		turndirection = 0;
	}
	if (key == GLUT_KEY_UP || key == GLUT_KEY_DOWN) {
		movedirection = 0;
	}
	if (key == GLUT_KEY_PAGE_UP || key == GLUT_KEY_PAGE_DOWN) {
		updirection = 0;
	}
}

//-- Regular key event callback 
//-- Enables use of regular keyboard inputs, such as 'q', 'w', ' '.
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
		case 'Q':
		case 'q': //Toggles wireframe via pressing 'q' or 'Q'
			if (!wireframe) {
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				wireframe = true;
			} else {
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				wireframe = false;
			} break;
	}
}

//-- Main: Initialize glut window and register call backs ------------------
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_DEPTH);
	glutInitWindowSize(1070, 600); 
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Themepark");
	initialize();

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special); 
	glutSpecialUpFunc(specialUp);
	glutTimerFunc(16, myTimer, 0);
	glutMainLoop();
	return 0;
}
