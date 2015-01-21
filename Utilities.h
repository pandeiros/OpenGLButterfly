#ifndef _UTILITIES_
#define _UTILITIES_

#include <string>
#include <iomanip>
#include <iostream>
#include "GLUT.H" 

#define PI  3.1415
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define MAX(a,b) (((a) > (b)) ? (a) : (b))

// Main variables and functions.
namespace Main {
    // Title
    static std::string TITLE = ">>> OpenGL Butterfly Project <<<";

    // Greeting message.
    static std::string GREETING_MESSAGE = "\
 >> Use 'w', 's', 'a', 'd' to zoom and move camera horizontally.\n\
 >> Use up and down arrows to move camera verticaly\n";


    // Prints formatted greeting message.
    static void printHeader () {
        unsigned int lineSize = 70;
        std::cout << std::setw (lineSize) << std::setfill ('=') << "\n";
        std::cout << "               " << TITLE << "\n";
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

    static float POSITION_X = 7.0f;      // Camera x position.
    static float POSITION_Y = 10.0f;     // Camera y position.
    static float POSITION_Z = -15.0f;      // Camera z position.
    static float DELTA_X = 0.0f;
    static float DELTA_Y = 0.0f;
    static float DELTA_Z = 0.0f;
    static float SPEED = 0.3f;

    /// Direction.

    static float DIR_X = -0.5f;      // Camera x direction.
    static float DIR_Y = -0.5f;      // Camera y direction.
    static float DIR_Z = 1.0f;     // Camera z direction.

    /// Rotation

    static float ANGLE_X = -140.0f;    // Camera x rotation angle.
    static float ANGLE_Y = 30.f;    // Camera y rotation angle.
    static float DELTA_ANGLE_X = 0.0f;      // Camera delta x rotation.
    static float DELTA_ANGLE_Y = 0.0f;      // Camera delta y rotation.
    static float ROTATION_MODIFIER = 0.2f;  // Camera rotation speed modifier.
}

// Light position, spot and intensity parameters.
namespace Light {

// Border values for linear attenuation.

#define MAX_LINEAR_ATT 0.1f
#define MIN_LINEAR_ATT 0.01f

    /// Light source coordinates.

    static float POS_X = 0.0f;      // Light x position.
    static float POS_Y = 20.0f;     // Light y position.
    static float POS_Z = -50.0f;    // Light z position.

    /// Spot directions.

    static float SPOT_X = 0.0f;     // Spot x direction.
    static float SPOT_Y = -1.0f;    // Spot y direction.
    static float SPOT_Z = 1.0f;     // Spot z direction.

    // Light linear attenuation.
    static float LINEAR_ATT = 0.05f;
}

#endif
