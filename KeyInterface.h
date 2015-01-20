#ifndef _KEY_INTERFACE_
#define _KEY_INTERFACE_

#include "GLUT.H"
#include "Utilities.h"

// Key bindings -------------------------------
#define KEY_EXIT_DEFAULT 27     // Escape key.
#define KEY_MOVE_RIGHT 'd'
#define KEY_MOVE_LEFT 'a'
#define KEY_MOVE_FORWARD 'w'
#define KEY_MOVE_BACKWARD 's'
#define KEY_MOVE_UP GLUT_KEY_UP
#define KEY_MOVE_DOWN GLUT_KEY_DOWN
#define KEY_LIGHT_DOWN GLUT_KEY_F4
#define KEY_LIGHT_UP GLUT_KEY_F5
// --------------------------------------------

namespace Keyboard {

    // Actions binded to key pressed event.
    void handlePressedKey (unsigned char key, int xx, int yy) {
        switch (key) {
            // Program termination.
            case KEY_EXIT_DEFAULT:
                exit (0);
                break;

                // Camera movement bindings.
            case KEY_MOVE_FORWARD:
                Camera::DELTA_X = Camera::SPEED;
                break;
            case KEY_MOVE_BACKWARD:
                Camera::DELTA_X = -Camera::SPEED;
                break;
            case KEY_MOVE_RIGHT:
                Camera::DELTA_Z = Camera::SPEED;
                break;
            case KEY_MOVE_LEFT:
                Camera::DELTA_Z = -Camera::SPEED;
                break;

            default:
                break;
        }
    }

    // Actions binded to key release event.
    void handleReleasedKey (unsigned char key, int xx, int yy)	// pressing this keys causes moving light source, moving tail, quiting program
    {
        switch (key) {

            // Camera stop movement bindings.
            case KEY_MOVE_FORWARD:
            case KEY_MOVE_BACKWARD:
                Camera::DELTA_X = 0.0;
                break;
            case KEY_MOVE_LEFT:
            case KEY_MOVE_RIGHT:
                Camera::DELTA_Z = 0.0;
                break;

            default:
                break;
        }
    }

    // Special GLUT pressed key handler.
    void pressedKeySpecial (int key, int x, int y) {

        // Y-axis camera movement.
        switch (key) {
            case KEY_MOVE_UP:
                Camera::DELTA_Y = Camera::SPEED;
                break;
            case KEY_MOVE_DOWN:
                Camera::DELTA_Y = -Camera::SPEED;
                break;
            case KEY_LIGHT_UP:
                Light::LINEAR_ATT = MAX (MIN_LINEAR_ATT, Light::LINEAR_ATT - 0.01f);
                break;
            case KEY_LIGHT_DOWN:
                Light::LINEAR_ATT = MIN (MAX_LINEAR_ATT, Light::LINEAR_ATT + 0.01f);
                break;
         
            default:
                break;
        }
    }

    // Special GLUT released key handler.
    void releasedKeySpecial (int key, int x, int y) {

        // Stop moving camera in Y-axis
        switch (key) {
            case KEY_MOVE_UP:
            case KEY_MOVE_DOWN:
                Camera::DELTA_Y = 0.0f;
                break;

            default:
                break;
            
        }
    }
}

#endif