#ifndef _KEY_INTERFACE_
#define _KEY_INTERFACE_

#include "GLUT.H"
#include "Utilities.h"

// Special GLUT pressed key handler.
void pressedKeySpecial (int key, int x, int y)
{
    // Default key assigment is to move camera
    switch (key) {
        case GLUT_KEY_UP:
            deltaMove = 0.5;
            break;
        case GLUT_KEY_DOWN:
            deltaMove = -0.5;
            break;
        case GLUT_KEY_LEFT:
            deltaMoveSideways = -0.5;
            break;
        case GLUT_KEY_RIGHT:
            deltaMoveSideways = 0.5;
            break;
    }
}

// Special GLUT released key handler.
void releasedKeySpecial (int key, int x, int y)	// releasing key up/down/left/right cancels camera movement
{
    switch (key) {
        case GLUT_KEY_UP:
        case GLUT_KEY_DOWN:
            deltaMove = 0.0;
            break;
        case GLUT_KEY_LEFT:
        case GLUT_KEY_RIGHT:
            deltaMoveSideways = 0.0;
            break;
    }
}

void processNormalKeys (unsigned char key, int xx, int yy)	// pressing this keys causes moving light source, moving tail, quiting program
{
    switch (key) {
        case 27:
        case 'q':
        case 'Q':
            exit (0);
            break;
        case '1':
            tileIsMoving = false;
            break;
        case '2':
            tileIsMoving = true;
            break;
        case '3':
            lightPositionZ > -50 ? lightPositionZ -= 1 : lightPositionZ;
            break;
        case '4':
            lightPositionZ < 50 ? lightPositionZ += 1 : lightPositionZ;
            break;
        case '5':
            lightPositionX > -50 ? lightPositionX -= 1 : lightPositionX;
            break;
        case '6':
            lightPositionX < 50 ? lightPositionX += 1 : lightPositionX;
            break;
    }
}

#endif