#ifndef _BUTTERFLY_
#define _BUTTERFLY_

#include <cmath>
#include <ctime>
#include "GLUT.H"

namespace Butterfly {

#define HEAD_COLOR glColor3ub(80, 80, 80);

    void drawBody () {
        GLUquadricObj *base = gluNewQuadric ();
        glPushMatrix ();
        {
            glTranslatef (0, 0, 0.25);
            gluCylinder (base, 0.6, 0.9, 1, 20, 20);
            gluCylinder (base, 1.2, 0.9, 1, 20, 20);
        }
        glPopMatrix ();

    }

    void drawHead () {
        GLUquadricObj *base = gluNewQuadric ();
        glPushMatrix ();
        {
            HEAD_COLOR
            gluSphere (base, 1.0, 30, 30);
        }
        glPopMatrix ();
    }

    void drawTail () {

    }

    void drawAntennae () {

    }

    void drawWings () {

    }

    // Butterfly render function.
    void renderButterfly () {
        drawBody ();
        drawHead ();
        drawTail ();
        drawWings ();
        drawAntennae ();
    }

}

#endif