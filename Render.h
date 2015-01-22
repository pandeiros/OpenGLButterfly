#ifndef _RENDER_
#define _RENDER_

#include <ctime>
#include "GLUT.H"
#include "Utilities.h"

namespace Render {

    // Perspective field of view angle.
    static float FOV_ANGLE = 60.0f;

    void init () {
        // Light parameters and positions.
        GLfloat grayAmbientLight[] = {0.1, 0.1, 0.1, 1.0};
        GLfloat whiteSpecularLight[] = {1.0, 1.0, 1.0, 1.0};
        GLfloat whiteDiffuseLight[] = {1.0, 1.0, 1.0, 1.0};
        GLfloat lightPosition[] = {Light::POS_X, Light::POS_Y, Light::POS_Z, 0.0};
        GLfloat sportDirection[] = {Light::SPOT_X, Light::SPOT_Y, Light::SPOT_Z};

        // Enable some magic stuff.
        glShadeModel (GL_SMOOTH);
        glEnable (GL_COLOR_MATERIAL);
        glEnable (GL_DEPTH_TEST);
        glEnable (GL_LIGHTING);
        glEnable (GL_LIGHT0);

        // Set up lightning.
        glLightfv (GL_LIGHT0, GL_AMBIENT, grayAmbientLight);
        glLightfv (GL_LIGHT0, GL_SPECULAR, whiteSpecularLight);
        glLightfv (GL_LIGHT0, GL_DIFFUSE, whiteDiffuseLight);
        glLightfv (GL_LIGHT0, GL_POSITION, lightPosition);
        glLightf (GL_LIGHT0, GL_LINEAR_ATTENUATION, Light::LINEAR_ATT);
        glLightf (GL_LIGHT0, GL_SPOT_CUTOFF, 90.0f);
        glLightf (GL_LIGHT0, GL_SPOT_EXPONENT, 2.f);
        glLightfv (GL_LIGHT0, GL_SPOT_DIRECTION, sportDirection);

        // Set up materials.
        GLfloat matSpecular[] = {1.0, 1.0, 1.0, 1.0};
        GLfloat matShininess[] = {5.0};
        glMaterialfv (GL_FRONT, GL_SPECULAR, matSpecular);
        glMaterialfv (GL_FRONT, GL_SHININESS, matShininess);

        glColorMaterial (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

        // Set initial camera position based on axis rotation.
        Camera::DIR_X = sin ((Camera::ANGLE_X + Camera::DELTA_ANGLE_X) / 180 * PI);
        Camera::DIR_Y = -sin ((Camera::ANGLE_Y + Camera::DELTA_ANGLE_Y) / 180 * PI);
        Camera::DIR_Z = -cos ((Camera::ANGLE_X + Camera::DELTA_ANGLE_X) / 180 * PI);

        // Start measuring time.
        Animation::begin = clock ();
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
        gluPerspective (FOV_ANGLE, ratio, 0.1, 300.0);
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

        Camera::DISTANCE = std::sqrt (
            std::sqrt (Camera::POSITION_X * Camera::POSITION_X + Camera::POSITION_Y * Camera::POSITION_Y) +
            Camera::POSITION_Z * Camera::POSITION_Z);
    }

    // Update light parameters.
    void updateLight () {
        GLfloat lightPosition[] = {Light::POS_X, Light::POS_Y, Light::POS_Z, 1.0};
        GLfloat spotDir[] = {Light::SPOT_X, Light::SPOT_Y, Light::SPOT_Z};
        glLightfv (GL_LIGHT0, GL_POSITION, lightPosition);
        glLightfv (GL_LIGHT0, GL_SPOT_DIRECTION, spotDir);
        glLightf (GL_LIGHT0, GL_LINEAR_ATTENUATION, Light::LINEAR_ATT);
    }

    // Main render function.
    void renderScene (void) {
        // Animation update.
        if (Animation::isAnimOn) {
            if (Animation::dt >= (1.f / (float)FPS)) {
                Animation::dt -= (1.f / (float)FPS);
                Animation::frame = (Animation::frame + 1) % FPS;
            }
            else {
                Animation::end = clock ();
                Animation::dt += (Animation::end - Animation::begin) / (float)CLOCKS_PER_SEC;
                Animation::begin = clock ();
            }
        }

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
            int FLOOR_SIZE = 70;

            // Fuchsia :D
            glColor3f (1.f, 0.0f, 1.f);
            glTranslatef (0.0f, -6.0f, 0.0f);
            for (int i = -FLOOR_SIZE; i < FLOOR_SIZE; ++i) {

                glBegin (GL_TRIANGLE_STRIP);
                for (int j = -FLOOR_SIZE; j < FLOOR_SIZE+20; ++j) {
                    glVertex3f (i, 0.0f, j);
                    glVertex3f (i + 1, 0.0f, j);
                }
                glEnd ();
            }
        }
        glPopMatrix ();
        // End creating floor

        //Render a cone to indicate light position and direction.
        glPushMatrix ();
        {
            GLfloat matEmmision[] = {0.9, 0.9, 0.9, 0.9};
            glMaterialfv (GL_FRONT, GL_EMISSION, matEmmision);

            GLUquadricObj *base = gluNewQuadric ();
            glColor3ub (200, 200, 200);
            glTranslatef (Light::POS_X, Light::POS_Y, Light::POS_Z);
            glRotatef (45, 1.0, 0.0, 0.0);
            glRotatef (180, 0.0, 1.0, 0.0);
            glutSolidCone (0.5, 1.5, 30, 30);

            GLfloat zeroEmmision[] = {0.0, 0.0, 0.0, 1.0};
            glMaterialfv (GL_FRONT, GL_EMISSION, zeroEmmision);
        }
        glPopMatrix ();


        // Render butterfly.
        Butterfly::renderButterfly ();


        // Make it visible.
        glutSwapBuffers ();
    }
}

#endif