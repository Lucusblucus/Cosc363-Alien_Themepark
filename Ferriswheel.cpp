/*
Module for Cosc363 assignment for drawing a ferris wheel 
*/
#include "Ferriswheel.hpp"
#include "objloader.hpp"

float wheel_angle = 0.1;

//For loading model
std::vector<vec3d>  out_vertices;
std::vector<vec2d>  out_uvs;
std::vector<vec3d>  out_normals;

void loadWheel(void)
{
	//Load Scene from OBJ file
	//loadOBJ("Objects/Scene.obj", out_vertices, out_uvs, out_normals);
	loadOBJ("Objects/Wheel.obj", out_vertices, out_uvs, out_normals);
}

void drawSeats(void)
{
glPushMatrix();
    //Draw 10 seats around the wheel
    for (size_t i = 0; i < 11; i++) {
        float ang = i * (360./10.);

        glPushMatrix();
            glRotatef(ang, 0, 0, 1);
            glTranslatef(0, -17, 0);

            glRotatef(-ang, 0, 0, 1); //Keep upright
            glRotatef(-wheel_angle, 0, 0, 1);

            glScalef(1.5, 0.2, 1);
            glutSolidCube(3); //Seat

        glPopMatrix();
    }
glPopMatrix();
}

void drawWheel(void)
{
glPushMatrix();

    glRotatef(9, 0, 0, 1);
    glRotatef(90, 0, 1, 0);
    glBegin(GL_TRIANGLES);
		for (size_t i = 0; i < out_vertices.size(); i++) {
			vec3d vec = out_vertices[i];
			vec3d norm = out_normals[i];
			vec2d tex = out_uvs[i];
			glTexCoord2f(tex.x, tex.y);
			glNormal3f(norm.x, norm.y, norm.z);
			glVertex3f(vec.x, vec.y, vec.z);
		}
	glEnd();

glPopMatrix();
}

void drawSupport(void)
{
    glColor4f(0.5, 0.5, 0.5, 1);
    GLUquadric *q = gluNewQuadric();	

        //Left front support
	glPushMatrix();
        glTranslatef(-0.4, 0, 2.5);
        glRotatef(90, 1, 0, 0);
        glRotatef(-30, 0, 1, 0);
		gluCylinder(q, .5, .5, 22, 20, 5);
	glPopMatrix();

        //Right front support
	glPushMatrix();
        glTranslatef(0.4, 0, 2.5);
        glRotatef(90, 1, 0, 0);
        glRotatef(30, 0, 1, 0);
		gluCylinder(q, .5, .5, 22, 20, 5);
	glPopMatrix();

        //Left back support
	glPushMatrix();
        glTranslatef(-0.4, 0, -2.5);
        glRotatef(90, 1, 0, 0);
        glRotatef(-30, 0, 1, 0);
		gluCylinder(q, .5, .5, 22, 20, 5);
	glPopMatrix();

        //right back support
	glPushMatrix();
        glTranslatef(0.4, 0, -2.5);
        glRotatef(90, 1, 0, 0);
        glRotatef(30, 0, 1, 0);
		gluCylinder(q, .5, .5, 22, 20, 5);
	glPopMatrix();
}
