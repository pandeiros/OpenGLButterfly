#ifndef _BUTTERFLY_
#define _BUTTERFLY_

#include <cmath>
#include <ctime>
#include "GLUT.H"

namespace Butterfly {

    // True if tail is moving.
    static bool tailIsMoving = false;
    
    // Butterfly render function.
    void renderButterfly () {
        GLUquadricObj *base = gluNewQuadric ();

        // move tail
        glPushMatrix ();
        {
            if (tailIsMoving == true) {
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
}

#endif