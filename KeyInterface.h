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
                Camera::DELTA_Y = Camera::SPEED;
                break;
            case KEY_MOVE_LEFT:
                Camera::DELTA_Y = -Camera::SPEED;
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
                Camera::DELTA_Y = 0.0;
                break;

            default:
                break;
        }
    }

    // Special GLUT pressed key handler.
    void pressedKeySpecial (int key, int x, int y) {
        // Default key assigment is to move camera
        switch (key) {
            case GLUT_KEY_UP:
                Camera::DELTA_X = 0.5;
                break;
            case GLUT_KEY_DOWN:
                Camera::DELTA_X = -0.5;
                break;
            case GLUT_KEY_LEFT:
                Camera::DELTA_Y = -0.5;
                break;
            case GLUT_KEY_RIGHT:
                Camera::DELTA_Y = 0.5;
                break;
        }
    }

    // Special GLUT released key handler.
    void releasedKeySpecial (int key, int x, int y)	// releasing key up/down/left/right cancels camera movement
    {
        switch (key) {
            case GLUT_KEY_UP:
            case GLUT_KEY_DOWN:
                Camera::DELTA_X = 0.0;
                break;
            case GLUT_KEY_LEFT:
            case GLUT_KEY_RIGHT:
                Camera::DELTA_Y = 0.0;
                break;
        }
    }
}

#endif