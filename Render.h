#ifndef _RENDER_
#define _RENDER_

#include "GLUT.H"

namespace Render {

    // Perspective field of view angle.
    static float FOV_ANGLE = 60.0f;

    // Light position and spot parameters.
    namespace Light {

        // Light source coordinates
        static float POS_X = 0.0f;
        static float POS_Y = 5.0f;
        static float POS_Z = 1.0f;

        // Spot direction
        static float SPOT_X = 0.0f;
        static float SPOT_Y = -1.0f;
        static float SPOT_Z = 0.0f;
    }

    void init () {
        GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
        GLfloat mat_shininess[] = {50.0};
        glShadeModel (GL_SMOOTH);
        glLightfv (GL_LIGHT0, GL_SPECULAR, mat_specular);
        glMaterialfv (GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv (GL_FRONT, GL_SHININESS, mat_shininess);
        glLightf (GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.1f);
        glLightf (GL_LIGHT0, GL_SPOT_CUTOFF, 120.0);
        glLightf (GL_LIGHT0, GL_SPOT_EXPONENT, 20.0);
        glEnable (GL_COLOR_MATERIAL);
        glEnable (GL_DEPTH_TEST);
        glEnable (GL_LIGHTING);
        glEnable (GL_LIGHT0);
        glColorMaterial (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    }

    // Reshape function.
    void changeSize (int w, int h) {
        // Check height to prevent dividing by 0.
        if (h == 0)
            h = 1;

        // Obtain ratio.
        float ratio = (float)w / (float)h;

        // Enter projection mode, transform and go back to model view mode.
        glMatrixMode (GL_PROJECTION);
        glLoadIdentity ();
        gluPerspective (FOV_ANGLE, ratio, 0.1, 100.0);
        glMatrixMode (GL_MODELVIEW);

        // Set viewport to cover entire window.
        glViewport (0, 0, w, h);
    }

    // Update camera parameters.
    void updateCameraPosition () {

        // Position was changed.
        if (Camera::DELTA_X || Camera::DELTA_Z || Camera::DELTA_Y) {
            Camera::POSITION_X += (Camera::DELTA_X * Camera::DIR_X - Camera::DELTA_Z * Camera::DIR_Z) * 0.1f;
            Camera::POSITION_Y += (Camera::DELTA_X * Camera::DIR_Y + Camera::DELTA_Y) * 0.1f;
            Camera::POSITION_Z += (Camera::DELTA_X * Camera::DIR_Z + Camera::DELTA_Z * Camera::DIR_X) * 0.1f;
        }
    }

    // Update light parameters.
    void updateLight () {
        GLfloat light_position[] = {Light::POS_X, Light::POS_Y, Light::POS_Z, 1.0};
        GLfloat spotDir[] = {Light::SPOT_X, Light::SPOT_Y, Light::SPOT_Z};
        glLightfv (GL_LIGHT0, GL_POSITION, light_position);
        glLightfv (GL_LIGHT0, GL_SPOT_DIRECTION, spotDir);
    }

    // Main render function.
    void renderScene (void) {
        // Clear buffers and load identity matrix.       
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity ();

        // Update camera and light
        updateCameraPosition ();
        gluLookAt (Camera::POSITION_X, Camera::POSITION_Y, Camera::POSITION_Z,
                   Camera::POSITION_X + Camera::DIR_X, Camera::POSITION_Y + Camera::DIR_Y, Camera::POSITION_Z + Camera::DIR_Z,
                   0.0f, 1.0f, 0.0f);
        updateLight ();

        // Create floor.
        glPushMatrix ();
        {
            int FLOOR_SIZE = 50;

            // Fuchsia :D
            glColor3f (1.f, 0.0f, 1.f);
            glTranslatef (0.0f, -6.0f, 0.0f);
            for (int i = -FLOOR_SIZE; i < FLOOR_SIZE; ++i) {

                glBegin (GL_TRIANGLE_STRIP);
                for ( int j = -FLOOR_SIZE; j < FLOOR_SIZE; ++j) {
                    glVertex3f (i, 0.0f, j);
                    glVertex3f (i + 1, 0.0f, j);
                }
                glEnd ();
            }
        }
        glPopMatrix ();
        // End creating floor

        
        // Render butterfly.
        glPushMatrix ();
        {
            glTranslatef (0.0, 0.0, 0.0);
            glColor3f (1.0f, 0.0f, 0.0f);
            Butterfly::renderButterfly ();
        }
        glPopMatrix ();
        // End redering butterfly.

        // Make it visible.
        glutSwapBuffers ();
    }
}

#endif