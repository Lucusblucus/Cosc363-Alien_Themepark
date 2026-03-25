#include "Alien.hpp"

void drawAlien(Alien* alien)
{
glPushMatrix();
    if (alien->FerrisRiding) {
        glTranslatef(0, -17, 0);
        glRotatef(-wheel_angle, 0, 0, 1);

    } else{
        glTranslatef(alien->x, alien->y, alien->z);
    }
    //glRotatef(180, 0, 1, 0);

    glPushMatrix(); //Pupil
        glColor4f(1., 1., 1., 1);
        glTranslatef(0, 0.64, 0.38);
        glutSolidSphere(0.1, 36, 17);
    glPopMatrix();

    glPushMatrix(); //Eye
        glColor4f(0., 0., 0., 1);
        glTranslatef(0, 0.6, 0.2);
        glutSolidSphere(0.25, 36, 17);
    glPopMatrix();

    glColor4f(0.4, 0.4, 0.4, 1);

    GLUquadric *q = gluNewQuadric();
    glPushMatrix(); //Left Arm
        glTranslatef(.5, -2, 0);
        glRotatef(30, 0, 0, 1);
        glTranslatef(-0.5, 2, 0);
        glTranslatef(0.5, 0.4, 0);
		gluCylinder(q, .1, .1, 1., 20, 5);
    glPopMatrix();

    //Body
    glScalef(1, 2, 1);
    glutSolidSphere(0.5, 36, 17);
glPopMatrix();
}