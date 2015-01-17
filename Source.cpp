/**
    Warsaw University of Technology
    Faculty of Electronics and Information Technology
    Author: Paweł Kaczyński

    OpenGL Project - "Butterfly"
*/
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <time.h>
#include <iostream>
#include "GLUT.H"

// Project dependencies.
#include "Utilities.h"
#include "KeyInterface.h"
#include "MouseInterface.h"
#include "Butterfly.h"
#include "Render.h"

// Program main function.
int main (int argc, char **argv)				
{
    // Print start-up message.
    Main::printHeader ();

    // Initialize window.
    glutInit (&argc, argv);
    glutInitDisplayMode (MODE);
    glutInitWindowPosition (Window::POSITION_X, Window::POSITION_Y);
    glutInitWindowSize (Window::WIDTH, Window::HEIGHT);
    glutCreateWindow (TITLE);

    // Keyboard callbacks.
    glutKeyboardFunc (Keyboard::handlePressedKey);	    // Pressed key handler.
    glutKeyboardUpFunc (Keyboard::handleReleasedKey);   // Released key handler.
    //glutSpecialFunc (pressSpecialKey);		// Pressed special key handler.
    //glutSpecialUpFunc (releaseSpecialKey);	// Released special key handler.

    // Mouse callbacks.
    glutMouseFunc (Mouse::mouseButton);		// Press/release button mouse handler.
    glutMotionFunc (Mouse::mouseMove);		// Mouse draggin handler.

    // Graphics callbacks.
    glutReshapeFunc (Render::changeSize);		// Window reshape function.
    glutDisplayFunc (Render::renderScene);	    // Scene display function.
    glutIdleFunc (Render::renderScene);         // Scene idle function (which is display function)

    // Ignore key repetition.
    glutIgnoreKeyRepeat (GLUT_DEVICE_IGNORE_KEY_REPEAT);					
    
    // And we begin...
    glutMainLoop ();							

    return 0;
}