/**
    Warsaw University of Technology
    Faculty of Electronics and Information Technology
    Author: Paweł Kaczyński

    OpenGL Project - "Butterfly"
*/
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <time.h>
#include <iostream>
#include "GLUT.H"
#include "Utilities.h"

// Canera position
float x = 3.0f;
float z = 8.0f;
float y = 3.0f;
float deltaMove = 0;
float deltaMoveSideways = 0;

// Camera direction
float lx = 0.0f;
float ly = 0.0f;
float lz = -1.0f;

// Camera direction - angle of rotation
float angleX = 0.0f;
float angleY = 0.0f;
float deltaAngleX = 0.0f;
float deltaAngleY = 0.0f;

// Mouse drag control
int xDragStart = -1;
int yDragStart = -1;

GLfloat light_position[] = {-2.0, 1.0, -2.0, 0.0};

bool tileIsMoving = false;

// Light source coordinates
double lightPositionX = 0.0;
double lightPositionY = 5.0;
double lightPositionZ = 1.0;

// Spot direction
double spotDirectionX = 0.0;
double spotDirectionY = -1.0;
double spotDirectionZ = 0.0;

void init () {
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = {50.0};
    GLfloat light_position[] = {lightPositionX, lightPositionY, lightPositionZ, 1.0};
    GLfloat spotDir[] = {spotDirectionX, spotDirectionY, spotDirectionZ};
    glShadeModel (GL_SMOOTH);
    glLightfv (GL_LIGHT0, GL_SPECULAR, mat_specular);
    glLightfv (GL_LIGHT0, GL_POSITION, light_position);
    glMaterialfv (GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv (GL_FRONT, GL_SHININESS, mat_shininess);
    glLightf (GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.1f);
    glLightf (GL_LIGHT0, GL_SPOT_CUTOFF, 120.0);
    glLightf (GL_LIGHT0, GL_SPOT_EXPONENT, 20.0);
    glLightfv (GL_LIGHT0, GL_SPOT_DIRECTION, spotDir);
    glEnable (GL_COLOR_MATERIAL);
    glEnable (GL_DEPTH_TEST);
    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
    glColorMaterial (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
}

void changeSize (int w, int h) {
    if (h == 0) h = 1;							// prevention division by zero
    float ratio = ((float)w) / ((float)h);		// window aspect ration
    glMatrixMode (GL_PROJECTION);				// projection matrix is active
    glLoadIdentity ();							// projection is reseted
    gluPerspective (45.0, ratio, 0.1, 100.0);	// perspective trasfromation
    glMatrixMode (GL_MODELVIEW);					// return to modelview mode
    glViewport (0, 0, w, h);						// set viewport to entire window
}

void displayShrimp () {
    GLUquadricObj *base = gluNewQuadric ();

    // move tail
    glPushMatrix ();
    {
        if (tileIsMoving == true) {
            glRotatef (sin (float (clock ()) / 100) * 5 + 5, 1, 0, 0);
        }
        else glRotatef (5, 1, 0, 0);
    }

    //tail
    glPushMatrix ();
    glRotatef (-20, 1, 0, 0);
    glTranslatef (0, 0.7, 0);
    glPushMatrix ();
    glTranslatef (0, 0, -4.75);
    glPushMatrix ();
    glTranslatef (0, 0, -2);
    glRotatef (90, 1, 0, 0);
    glBegin (GL_TRIANGLE_FAN);
    glVertex3f (0, 0, 0);
    glVertex3f (1.0, 0, -0.2);
    glVertex3f (0.8, 0.6, -0.1);
    glVertex3f (0.4, 1.0, -0.2);
    glVertex3f (0, 1.0, 0);
    glVertex3f (-0.4, 1.0, -0.2);
    glVertex3f (-0.8, 0.6, -0.1);
    glVertex3f (-1.0, 0, -0.2);
    glEnd ();
    glPopMatrix ();
    glRotatef (-180, 0.0, 1, 0);
    glutSolidCone (0.4, 2, 20, 20);
    glPopMatrix ();
    glPopMatrix ();

    //segments
    glPushMatrix ();
    glRotatef (-15, 1, 0, 0);
    for (int i = 0; i < 6; ++i) {

        glPushMatrix ();
        glRotatef (5 + 3 * i, 1, 0, 0);
        glTranslatef (0, -0.2, -5.25 + i*0.75);
        glRotatef (-10, 1, 0, 0);
        gluCylinder (base, 0.4 + 0.075*i, 0.6 + 0.1*i, 1, 20, 20);
        glPushMatrix ();
        glRotatef (sin (clock () / 50 + i) * 15, 0, 0, 1);
        glTranslatef (0, -0.2, 1);
        glRotatef (90, 0, 1, 0);
        glTranslatef (0, 0, 0.8);
        glRotatef (-90, 0, 1, 0);
        glBegin (GL_TRIANGLE_STRIP);
        glVertex3f (0, 0, 0);
        glVertex3f (-0.1, 0.2, 0);
        glVertex3f (0.2, 0.2, 0);
        glVertex3f (0.3, 0.5, 0);
        glVertex3f (0.5 + i*0.1, -0.5 - i*0.3, 0.1);
        glEnd ();
        glPopMatrix ();
        glPushMatrix ();
        glRotatef (sin (clock () / 50 + i) * 15, 0, 0, 1);
        glTranslatef (0, -0.2, 1);
        glRotatef (-90, 0, 1, 0);
        glTranslatef (0, 0, 0.8);
        glRotatef (90, 0, 1, 0);
        glBegin (GL_TRIANGLE_STRIP);
        glVertex3f (0, 0, 0);
        glVertex3f (0.1, 0.2, 0);
        glVertex3f (-0.2, 0.2, 0);
        glVertex3f (-0.3, 0.5, 0);
        glVertex3f (-0.5 - i*0.1, -0.5 - i*0.3, 0.1);
        glEnd ();
        glPopMatrix ();
        glPopMatrix ();
    }
    glPopMatrix ();

    glTranslatef (0, 0, -0.75);
    gluCylinder (base, 1.0, 1.2, 1, 20, 20);
    glPopMatrix ();
    glPopMatrix ();
    // body
    glPushMatrix ();
    glTranslatef (0, 0, 0.25);
    gluCylinder (base, 0.6, 0.9, 1, 20, 20);
    gluCylinder (base, 1.2, 0.9, 1, 20, 20);
    glPopMatrix ();

    // draw head
    glTranslatef (0, 0, 1);
    glutSolidCone (0.9, 2.5, 20, 20);

    // left moustache
    glPushMatrix ();
    glTranslatef (0, -0.2, 1);
    glRotatef (30, 0, 1, 0);
    glColor3f (1, 0, 0);
    glBegin (GL_POLYGON);
    glVertex3f (0, 0, 0);
    glVertex3f (0.0, 0.2, 0.0);
    glVertex3f (0.0, 0.2, 1.0);
    glVertex3f (0.0, 0.0, 1.0);
    glEnd ();
    glBegin (GL_POLYGON);
    glVertex3f (0.0, 0.2, 1.0);
    glVertex3f (0.0, 0.0, 1.0);
    glVertex3f (-1.0, 0.1, 4.0);
    glEnd ();
    glPopMatrix ();

    // right moustache
    glPushMatrix ();
    glTranslatef (0, -0.2, 1);
    glRotatef (-30, 0, 1, 0);
    glColor3f (1, 0, 0);
    glBegin (GL_POLYGON);
    glVertex3f (0, 0, 0);
    glVertex3f (0.0, 0.2, 0.0);
    glVertex3f (0.0, 0.2, 1.0);
    glVertex3f (0.0, 0.0, 1.0);
    glEnd ();
    glBegin (GL_POLYGON);
    glVertex3f (0.0, 0.2, 1.0);
    glVertex3f (0.0, 0.0, 1.0);
    glVertex3f (1.0, 0.1, 4.0);
    glEnd ();
    glPopMatrix ();

    // draw eyes
    glRotatef (-90, 0, 0, 1);
    glTranslatef (-0.4, 0, 1);
    glPushMatrix ();
    glTranslatef (0, 0.3, 0);
    glColor3f (1, 1, 1);
    glutSolidSphere (0.3, 30, 30);
    glTranslatef (0, 0, 0.23);
    glColor3f (0, 0, 0);
    glutSolidSphere (0.1, 12, 12);
    glPopMatrix ();
    glPushMatrix ();
    glTranslatef (0, -0.3, 0);
    glColor3f (1, 1, 1);
    glutSolidSphere (0.3, 30, 30);
    glTranslatef (0, 0, 0.23);
    glColor3f (0, 0, 0);
    glutSolidSphere (0.1, 12, 12);
    glPopMatrix ();
}

void updatePosition ()	// updates camera coordinates 
{
    if (deltaMove || deltaMoveSideways) {

        x += (deltaMove * lx - deltaMoveSideways * lz) * 0.1f;
        z += (deltaMove * lz + deltaMoveSideways * lx) * 0.1f;
        y += deltaMove * ly * 0.1f;
    }
}

void renderScene (void) {
    updatePosition ();
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);				// clear buffers
    glLoadIdentity ();												// reset transformations
    gluLookAt (x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);	// set the camera

    init ();

    glPushMatrix ();
    glTranslatef (lightPositionX, 5.0, lightPositionZ);
    glutSolidSphere (0.3, 30, 30);
    glPopMatrix ();

    glPushMatrix ();
    glColor3f (0.1f, 0.0f, 0.3f);
    glTranslatef (0.0f, -6.0f, 0.0f);
    for (int i = -50; i < 50; i++) {
        glBegin (GL_TRIANGLE_STRIP);
        for (int j = -50; j < 50; j++) {
            glVertex3f (i, 0.0f, j);
            glVertex3f (i + 1, 0.0f, j);
        }
        glEnd ();
    }
    glPopMatrix ();

    glPushMatrix ();
    glTranslatef (0.0, 0.0, 0.0);
    glColor3f (1.0f, 0.0f, 0.0f);
    displayShrimp ();
    glPopMatrix ();
    glColor3f (1.0f, 1.0f, 1.0f);
    glutSwapBuffers ();
}

void mouseMove (int x, int y)				// processing of mouse drag
{
    if (xDragStart >= 0 && yDragStart >= 0) // this will only be true when the left button is down 
    {
        deltaAngleX = (x - xDragStart) * 0.003f;
        lx = sin (angleX + deltaAngleX);
        lz = -cos (angleX + deltaAngleX);
        deltaAngleY = (y - yDragStart) * 0.003f;
        ly = sin (angleY - deltaAngleY);
    }
}

void mouseButton (int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) 		// only start motion if the left button is pressed
    {
        if (state == GLUT_UP)				// when the button is released
        {
            angleX += deltaAngleX;
            angleY -= deltaAngleY;
            xDragStart = -1;
            yDragStart = -1;
        }
        else								// state = GLUT_DOWN 
        {
            xDragStart = x;
            yDragStart = y;
        }
    }
}

// Program main function.
int main (int argc, char **argv)				
{
    // Print start-up message.
    Main::printHeader ();

    // Initialize window.
    glutInit (&argc, argv);
    glutInitDisplayMode (MODE);
    glutInitWindowPosition (Window::POSITION_X, Window::POSITION_Y);
    glutInitWindowSize (Window::WIDTH, Window::HEIGHT);
    glutCreateWindow (TITLE);

    // register callbacks
    glutReshapeFunc (changeSize);			// window reshape callback
    glutDisplayFunc (renderScene);			// (re)display callback
    glutIdleFunc (renderScene);
    glutIgnoreKeyRepeat (1);					// ignore key repeat when holding key down
    glutMouseFunc (mouseButton);				// process mouse button push/release
    glutMotionFunc (mouseMove);				// process mouse dragging motion
    //glutKeyboardFunc (processNormalKeys);	// process standard key clicks
    //glutSpecialFunc (pressSpecialKey);		// process special key pressed
    //glutSpecialUpFunc (releaseSpecialKey);	// process special key release

    glutMainLoop ();							// enter GLUT event processing cycle

    return 0;
}