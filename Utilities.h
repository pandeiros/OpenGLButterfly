#ifndef _UTILITIES_
#define _UTILITIES_

#include <string>
#include <iomanip>
#include <iostream>
#include "GLUT.H" 

#define PI  3.1415

// Main variables and functions.
namespace Main {
    // Title
    static std::string TITLE = ">>> OpenGL Butterfly Project <<<";

    // Greeting message.
    static std::string GREETING_MESSAGE = "\
 >> Use 'w', 's', 'a', 'd' to move camera around.\n";


    // Prints formatted greeting message.
    static void printHeader () {
        unsigned int lineSize = 45;
        std::cout << std::setw (lineSize) << std::setfill ('=') << "\n";
        std::cout << "      " << TITLE << "\n";
        std::cout << std::setw (lineSize) << std::setfill ('-') << "\n";
        std::cout << GREETING_MESSAGE;
        std::cout << std::setw (lineSize) << std::setfill ('=') << "\n";
    }
}

// Window parameters.
namespace Window {
    // Position.
    enum Position {
        POSITION_X = 300,    // Window x position.
        POSITION_Y = 200    // Window y position.
    };

    // Size.
    enum Size {
        WIDTH = 900,    // Window width.
        HEIGHT = 500    // Window height.
    };

    // Window title.
#define TITLE "Butterfly"

// Display mode.
#define MODE (GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA)

}

// Camera position and movement parameters.
namespace Camera {
    /// Position.     

    static float POSITION_X = 8.0f;      // Camera x position.
    static float POSITION_Y = 3.0f;     // Camera y position.
    static float POSITION_Z = 12.0f;      // Camera z position.
    static float DELTA_X = 0.0f;
    static float DELTA_Y = 0.0f;
    static float SPEED = 0.3f;

    /// Direction.

    static float DIR_X = 0.0f;      // Camera x direction.
    static float DIR_Y = 0.0f;      // Camera y direction.
    static float DIR_Z = -1.0f;     // Camera z direction.

    /// Rotation

    static float ANGLE_X = 0.0f;    // Camera x rotation angle.
    static float ANGLE_Y = 0.0f;    // Camera y rotation angle.
    static float DELTA_ANGLE_X = 0.0f;      // Camera delta x rotation.
    static float DELTA_ANGLE_Y = 0.0f;      // Camera delta y rotation.
    static float ROTATION_MODIFIER = 0.5f;  // Camera rotation speed modifier.
}
#endif
