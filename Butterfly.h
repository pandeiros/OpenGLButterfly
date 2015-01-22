#ifndef _BUTTERFLY_
#define _BUTTERFLY_

#include <cmath>
#include <ctime>
#include "GLUT.H"
#include "gle.h"
#include "Utilities.h"

namespace Butterfly {

    // Colors.
#define COLOR_BLACK glColor3ub(0,0,0)
#define HEAD_COLOR glColor3ub(45, 45, 45)
#define BODY_COLOR glColor3ub(30, 30, 30)
#define WING_BORDER_COLOR glColor3ub(240, 240, 240)
#define WING_FILL_COLOR_YELLOW glColor3ub(250, 230, 20)
#define WING_FILL_COLOR_BLUE glColor3ub(85, 134, 210)
#define WING_FILL_COLOR_RED glColor3ub(240, 50, 5)
#define WING_FILL_COLOR_GREEN glColor3ub(160, 220, 60)

    // Line sizes.
#define WING_BORDER_SIZE 5.f
#define ANTENNA_SIZE 5.f

    // Extrusion contour
    static gleDouble contour[MAX_BEZIER_PREC + 2][2];

    // Up vector.
    static gleDouble up[3] = {0.0, 1.0, 0.0};

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

    // Antennae draw function.
    // Two line strips created with bezier curves.
    void drawAntennae () {

        // Line width modifier based on Camera distance.
        float sizeModifier = MAX (10.f, Camera::DISTANCE) / 10.f;

        // Right antenna.
        glPushMatrix ();
        {
            COLOR_BLACK;
            glTranslatef (0.3f, 0.3f, 0.f);
            glLineWidth (ANTENNA_SIZE / sizeModifier);
            glBegin (GL_LINE_STRIP);
            for (unsigned int t = 0; t <= Bezier::BEZIER_PRECISION; ++t) {
                glVertex3f (
                    Bezier::getBezierPoint (false, false, true, t / (float)Bezier::BEZIER_PRECISION, 0),
                    Bezier::getBezierPoint (false, false, true, t / (float)Bezier::BEZIER_PRECISION, 1),
                    Bezier::getBezierPoint (false, false, true, t / (float)Bezier::BEZIER_PRECISION, 2)
                    );
            }
            glEnd ();
        }
        glPopMatrix ();

        // Left antenna.
        glPushMatrix ();
        {
            COLOR_BLACK;
            glTranslatef (-0.3f, 0.3f, 0.f);
            glLineWidth (ANTENNA_SIZE / sizeModifier);
            glBegin (GL_LINE_STRIP);
            for (unsigned int t = 0; t <= Bezier::BEZIER_PRECISION; ++t) {
                glVertex3f (
                    Bezier::getBezierPoint (false, false, false, t / (float)Bezier::BEZIER_PRECISION, 0),
                    Bezier::getBezierPoint (false, false, false, t / (float)Bezier::BEZIER_PRECISION, 1),
                    Bezier::getBezierPoint (false, false, false, t / (float)Bezier::BEZIER_PRECISION, 2)
                    );
            }
            glEnd ();
        }
        glPopMatrix ();
    }

    // Wings draw function.
    // Four wings
    void drawWings () {
        float sizeModifier = MAX (10.f, Camera::DISTANCE) / 10.f;
        if (Animation::isAnimOn)
            Animation::wingInclination += Animation::modifier * 2.f * PI / (float)Animation::FPS;
        float rotIncl = sin (Animation::wingInclination);

        float angle = -45.f;
        float deltaPos = 3.f;

        // Lower right.
        glPushMatrix ();
        {
            // Animate and translate.
            glTranslatef (0.f, 0.f, 5.5f);
            glRotatef (angle * rotIncl + 15, 0.0, 0.0, 1.0);

            // Wing border
            glPushMatrix ();
            {
                WING_BORDER_COLOR;
                glLineWidth (WING_BORDER_SIZE / sizeModifier);
                glBegin (GL_LINE_STRIP);
                for (unsigned int t = 0; t <= Bezier::BEZIER_PRECISION; ++t) {
                    glVertex3f (
                        contour[t][0] = Bezier::getBezierPoint (true, true, true, t / (float)Bezier::BEZIER_PRECISION, 0),
                        Bezier::getBezierPoint (true, true, true, t / (float)Bezier::BEZIER_PRECISION, 1),
                        contour[t][1] = Bezier::getBezierPoint (true, true, true, t / (float)Bezier::BEZIER_PRECISION, 2)
                        );
                }
                glEnd ();
            }
            glPopMatrix ();

            // Wing fill.
            WING_FILL_COLOR_YELLOW;
            glTranslatef (0.1f, -0.05f, 0.1f);
            glScalef (0.99, 1.0, 0.99);
            glRotatef (90.f, 1.f, 0.f, 0.f);
            gleScrew (Bezier::BEZIER_PRECISION + 1, contour, NULL, up, 0, -0.1, 0);
        }
        glPopMatrix ();

        // Upper right.
        glPushMatrix ();
        {
            // Animate and translate.
            glTranslatef (0.f, 0.f, 4.5f);
            glRotatef (angle * rotIncl + 15, 0.0, 0.0, 1.0);

            // Wing border
            glPushMatrix ();
            {
                WING_BORDER_COLOR;
                glLineWidth (WING_BORDER_SIZE / sizeModifier);

                glLineWidth (WING_BORDER_SIZE / sizeModifier);
                glBegin (GL_LINE_STRIP);
                for (unsigned int t = 0; t <= Bezier::BEZIER_PRECISION; ++t) {
                    glVertex3f (
                        contour[t][0] = Bezier::getBezierPoint (true, false, true, t / (float)Bezier::BEZIER_PRECISION, 0),
                        Bezier::getBezierPoint (true, false, true, t / (float)Bezier::BEZIER_PRECISION, 1),
                        contour[t][1] = Bezier::getBezierPoint (true, false, true, t / (float)Bezier::BEZIER_PRECISION, 2)
                        );
                }
                glEnd ();
            }
            glPopMatrix ();

            WING_FILL_COLOR_GREEN;
            glTranslatef (0.1f, -0.05f, -0.1f);
            glScalef (0.99, 1.0, 0.99);
            glRotatef (90.f, 1.f, 0.f, 0.f);
            gleScrew (Bezier::BEZIER_PRECISION + 1, contour, NULL, up, 0, -0.1, 0);
        }
        glPopMatrix ();

        // Lower left.
        glPushMatrix ();
        {

            // Animate and translate.
            glTranslatef (0.f, 0.f, 5.5f);
            glRotatef (-angle * rotIncl -15, 0.0, 0.0, 1.0);

            // Wing border
            glPushMatrix ();
            {
                WING_BORDER_COLOR;
                glLineWidth (WING_BORDER_SIZE / sizeModifier);
                glBegin (GL_LINE_STRIP);
                for (unsigned int t = 0; t <= Bezier::BEZIER_PRECISION; ++t) {
                    glVertex3f (
                        contour[t][0] = Bezier::getBezierPoint (true, true, false, t / (float)Bezier::BEZIER_PRECISION, 0),
                        Bezier::getBezierPoint (true, true, false, t / (float)Bezier::BEZIER_PRECISION, 1),
                        contour[t][1] = Bezier::getBezierPoint (true, true, false, t / (float)Bezier::BEZIER_PRECISION, 2)
                        );
                }
                glEnd ();
            }
            glPopMatrix ();

            WING_FILL_COLOR_BLUE;
            glTranslatef (-0.1f, -0.05f, 0.1f);
            glScalef (0.99, 1.0, 0.99);
            glRotatef (90.f, 1.f, 0.f, 0.f);
            gleScrew (Bezier::BEZIER_PRECISION + 1, contour, NULL, up, 0, -0.1, 0);
        }
        glPopMatrix ();

        // Upper left.
        glPushMatrix ();
        {
            // Animate and translate.
            glTranslatef (0.f, 0.f, 4.5f);
            glRotatef (-angle * rotIncl -15, 0.0, 0.0, 1.0);

            // Wing border
            glPushMatrix ();
            {
                WING_BORDER_COLOR;
                glLineWidth (WING_BORDER_SIZE / sizeModifier);
                glBegin (GL_LINE_STRIP);
                for (unsigned int t = 0; t <= Bezier::BEZIER_PRECISION; ++t) {
                    glVertex3f (
                        contour[t][0] = Bezier::getBezierPoint (true, false, false, t / (float)Bezier::BEZIER_PRECISION, 0),
                        Bezier::getBezierPoint (true, false, false, t / (float)Bezier::BEZIER_PRECISION, 1),
                        contour[t][1] = Bezier::getBezierPoint (true, false, false, t / (float)Bezier::BEZIER_PRECISION, 2)
                        );
                }
                glEnd ();
            }
            glPopMatrix ();

            WING_FILL_COLOR_RED;
            glTranslatef (-0.1f, -0.05f, -0.1f);
            glScalef (0.99, 1.0, 0.99);
            glRotatef (90.f, 1.f, 0.f, 0.f);
            gleScrew (Bezier::BEZIER_PRECISION + 1, contour, NULL, up, 0, -0.1, 0);
        }
        glPopMatrix ();
    }

    // Butterfly render function.
    void renderButterfly () {
        drawBody ();
        drawHead ();
        drawTail ();
        drawAntennae ();
        drawWings ();
    }
}

#endif