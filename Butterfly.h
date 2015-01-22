#ifndef _BUTTERFLY_
#define _BUTTERFLY_

#include <cmath>
#include <ctime>
#include "GLUT.H"
#include "gle.h"
#include "Utilities.h"

namespace Butterfly {

#define HEAD_COLOR glColor3ub(45, 45, 45)
#define BODY_COLOR glColor3ub(30, 30, 30)
#define WING_COLOR glColor3ub(200, 150, 100)

    // TEMP
    static int b = 2;

    // Body draw function.
    // Contains of one dark sphere, expanded in one axis.
    void drawBody () {
        GLUquadricObj *base = gluNewQuadric ();
        glPushMatrix ();
        {
            BODY_COLOR;

            glTranslatef (0.f, 0.f, 5.f);
            glScalef (1.f, 1.f, 5.f);
            gluSphere (base, 1.0, 30, 30);
        }
        glPopMatrix ();
    }

    // Head draw function.
    // Contains of one dark sphere, expanded a little bit in one axis.
    void drawHead () {
        GLUquadricObj *base = gluNewQuadric ();
        glPushMatrix ();
        {
            HEAD_COLOR;

            glTranslatef (0.f, 0.f, 0.3f);
            glScalef (1.f, 1.f, 1.35f);
            gluSphere (base, 0.7, 30, 30);
        }
        glPopMatrix ();
    }

    // Tail draw function.
    // Contains of one slim cylinder and one small sphere at the end.
    void drawTail () {
        GLUquadricObj *base = gluNewQuadric ();
        glPushMatrix ();
        {
            BODY_COLOR;

            // Cylinder.
            glPushMatrix ();
            {
                glTranslatef (0.f, 0.f, 9.5f);
                gluCylinder (base, 0.3, 0.15, 5.0, 20, 20);
            }
            glPopMatrix ();

            // Sphere.
            glPushMatrix ();
            {
                glTranslatef (0.f, 0.f, 14.5f);
                glScalef (1.f, 1.f, 1.5f);
                gluSphere (base, 0.15, 30, 30);
            }
            glPopMatrix ();
        }
        glPopMatrix ();
    }

    void drawAntennae () {

    }

   
    void drawWings () {

        // Lower right.
        glPushMatrix ();
        {
            WING_COLOR;
            glTranslatef (0.f, 0.f, 5.5f);
            glLineWidth (5.f);
            glBegin (GL_LINE_STRIP);
            for (unsigned int t = 0; t <= Bezier::BEZIER_PRECISION; ++t) {
                glVertex3f (
                    Bezier::getBezierPoint (true, true, t / (float)Bezier::BEZIER_PRECISION, 0),
                    Bezier::getBezierPoint (true, true, t / (float)Bezier::BEZIER_PRECISION, 1),
                    Bezier::getBezierPoint (true, true, t / (float)Bezier::BEZIER_PRECISION, 2)
                    );
            }
            glEnd ();
        }
        glPopMatrix ();

        // Upper right.
        glPushMatrix ();
        {
            WING_COLOR;
            glTranslatef (0.f, 0.f, 4.5f);
            glLineWidth (5.f);
            glBegin (GL_LINE_STRIP);
            for (unsigned int t = 0; t <= Bezier::BEZIER_PRECISION; ++t) {
                glVertex3f (
                    Bezier::getBezierPoint (false, true, t / (float)Bezier::BEZIER_PRECISION, 0),
                    Bezier::getBezierPoint (false, true, t / (float)Bezier::BEZIER_PRECISION, 1),
                    Bezier::getBezierPoint (false, true, t / (float)Bezier::BEZIER_PRECISION, 2)
                    );
            }
            glEnd ();
        }
        glPopMatrix ();

        // Lower left.
        glPushMatrix ();
        {
            WING_COLOR;
            glTranslatef (0.f, 0.f, 5.5f);
            glLineWidth (5.f);
            glBegin (GL_LINE_STRIP);
            for (unsigned int t = 0; t <= Bezier::BEZIER_PRECISION; ++t) {
                glVertex3f (
                    Bezier::getBezierPoint (true, false, t / (float)Bezier::BEZIER_PRECISION, 0),
                    Bezier::getBezierPoint (true, false, t / (float)Bezier::BEZIER_PRECISION, 1),
                    Bezier::getBezierPoint (true, false, t / (float)Bezier::BEZIER_PRECISION, 2)
                    );
            }
            glEnd ();
        }
        glPopMatrix ();

        // Upper left.
        glPushMatrix ();
        {
            WING_COLOR;
            glTranslatef (0.f, 0.f, 4.5f);
            glLineWidth (5.f);
            glBegin (GL_LINE_STRIP);
            for (unsigned int t = 0; t <= Bezier::BEZIER_PRECISION; ++t) {
                glVertex3f (
                    Bezier::getBezierPoint (false, false, t / (float)Bezier::BEZIER_PRECISION, 0),
                    Bezier::getBezierPoint (false, false, t / (float)Bezier::BEZIER_PRECISION, 1),
                    Bezier::getBezierPoint (false, false, t / (float)Bezier::BEZIER_PRECISION, 2)
                    );
            }
            glEnd ();
        }
        glPopMatrix ();
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

///*gleDouble tab[][3] = {{5.0,5.0,5.0}, {6.0,5.0,5.0}, {6.0,6.0,5.0 }, {5.0,6.0,5.0}};
//float color[][3] = {{0.f,0.f,0.f}, {0.2,0.2,0.2}, {0.3,0.3,0.3}, {0.5,0.5,0.5}};*/
//glPushMatrix ();
//{
//    //glePolyCylinder (5, tab, color, 4.0);	
//    //GLfloat buffer[1024] = {0};
//    //    glFeedbackBuffer (3, GL_3D, buffer);
//    //    glRenderMode (GL_FEEDBACK);
//    //GLfloat ctrlpoints[4][3] = {
//    //    {-4.0, -4.0, 0.0}, {-2.0, 4.0, 0.0},
//    //    {2.0, -4.0, 0.0}, {4.0, 4.0, 0.0}};
//    //glMap1f (GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[0][0]);
//    //glEnable (GL_MAP1_VERTEX_3);
//    //glColor3f (1.0, 1.0, 1.0);
//    ////glPassThrough (1.0);
//    //glBegin (GL_LINE_STRIP);
//    //for (int i = 0; i <= WING_PRECISION; i++)
//    //    glEvalCoord1f ((GLfloat)i / (double)WING_PRECISION);
//    //glVertex3fv (ctrlpoints[1]);
//    //glEnd ();
//    //glRenderMode (GL_RENDER);
//
//    GLfloat feedBuffer[1024];
//    GLint size;
//
//    //glMatrixMode (GL_PROJECTION);
//    //glLoadIdentity ();
//    //glOrtho (0.0, 100.0, 0.0, 100.0, 0.0, 1.0);
//
//    //glClearColor (0.0, 0.0, 0.0, 0.0);
//    //glClear (GL_COLOR_BUFFER_BIT);
//    drawGeometry (GL_RENDER);
//    glFeedbackBuffer (1024, GL_3D_COLOR, feedBuffer);
//    glRenderMode (GL_FEEDBACK);
//    drawGeometry (GL_FEEDBACK);
//
//    size = glRenderMode (GL_RENDER);
//    if (b > 0) {
//        printBuffer (size, feedBuffer);
//        b--;
//    }
//
//    //glRenderMode (GL_RENDER);
//
//
//    //    GLfloat ctrlpoints[4][3] =
//    //    {
//    //        {-4.0, -4.0, 0.0}, {-2.0, 4.0, 0.0},
//    //        {2.0, -4.0, 0.0}, {4.0, 4.0, 0.0}
//    //    };
//
//    //    glMap1f (GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[0][0]);
//    //    glEnable (GL_MAP1_VERTEX_3);
//
//    //    GLfloat feedBuffer[1024];
//    //    glFeedbackBuffer (1024, GL_3D, feedBuffer);
//    //    glRenderMode (GL_FEEDBACK);
//
//    //    glPointSize (5);
//    //    glColor3ub (255, 255, 255);
//    //    glPassThrough (1.0);
//    //    //glBegin (GL_POINTS);
//    //    glNormal3f (0.0, 0.0, 1.0);
//    //    glVertex3f (ctrlpoints[1][0], ctrlpoints[1][1], ctrlpoints[1][2]);
//    //    glVertex3f (ctrlpoints[0][0], ctrlpoints[0][1], ctrlpoints[0][2]);
//    //    glVertex3f (ctrlpoints[2][0], ctrlpoints[2][1], ctrlpoints[2][2]);
//    //    //glEnd ();
//    //    glPointSize (5);
//    //    glBegin (GL_LINE_STRIP);
//    //    for (int i = 0; i <= 30; ++i) {
//    //        GLfloat t = GLfloat (i) / 30;
//    //        glEvalCoord1f (t);
//    //     
//    //    }
//
//    //    glEnd ();
//    //    glRenderMode (GL_RENDER);
//
//    //    glPointSize (5);
//    //    glColor3ub (255, 255, 255);
//    //    glBegin (GL_POINTS);
//    //    glVertex3f (ctrlpoints[0][0], ctrlpoints[0][1], ctrlpoints[0][2]);
//    //    glVertex3f (ctrlpoints[1][0], ctrlpoints[1][1], ctrlpoints[1][2]);
//    //    glEnd ();
//
//    //    glBegin (GL_LINE_STRIP);
//    //    for (int i = 0; i <= 30; ++i) {
//    //        GLfloat t = GLfloat (i) / 30;
//    //        glEvalCoord1f (t);
//    //    }
//    //    glEnd ();
//
//    if (b > 0) {
//        for (int i = 0; i < WING_PRECISION * 5; ++i)
//            std::cout << feedBuffer[i] << "\n";
//        std::cout << "\n";
//        b = false;
//    }
//}
//glPopMatrix ();