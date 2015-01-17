#ifndef _RENDER_
#define _RENDER_

#include "GLUT.H"

namespace Render {
    // Light source coordinates
    float lightPositionX = 0.0f;
    float lightPositionY = 5.0f;
    float lightPositionZ = 1.0f;

    // Spot direction
    float spotDirectionX = 0.0f;
    float spotDirectionY = -1.0f;
    float spotDirectionZ = 0.0f;

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

    void updatePosition ()	// updates camera coordinates 
    {
        if (Camera::DELTA_X || Camera::DELTA_Y) {

            Camera::POSITION_X += (Camera::DELTA_X * Camera::DIR_X - Camera::DELTA_Y * Camera::DIR_Z) * 0.1f;
            Camera::POSITION_Z += (Camera::DELTA_X * Camera::DIR_Z + Camera::DELTA_Y * Camera::DIR_X) * 0.1f;
            Camera::POSITION_Y += Camera::DELTA_X * Camera::DIR_Y * 0.1f;
        }
    }

    void renderScene (void) {
        updatePosition ();
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);				// clear buffers
        glLoadIdentity ();												// reset transformations
        gluLookAt (Camera::POSITION_X, Camera::POSITION_Y, Camera::POSITION_Z, Camera::POSITION_X + Camera::DIR_X, Camera::POSITION_Y + Camera::DIR_Y, Camera::POSITION_Z + Camera::DIR_Z, 0.0f, 1.0f, 0.0f);	// set the camera

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
        Butterfly::renderButterfly ();
        glPopMatrix ();
        glColor3f (1.0f, 1.0f, 1.0f);
        glutSwapBuffers ();
    }
}

#endif