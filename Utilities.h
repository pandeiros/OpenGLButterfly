#ifndef _UTILITIES_
#define _UTILITIES_

#include <string>
#include <iomanip>
#include <iostream>
#include "GLUT.H" 

// Main variables and functions.
namespace Main {
    // Title
    static std::string TITLE = ">>> OpenGL Butterfly Project <<<";

    // Greeting message.
    static std::string GREETING_MESSAGE = "\
Here will be key bindings.\n";


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

    static float POSITION_X = 3.f;      // Camera x position.
    static float POSITION_Y = 10.f;     // Camera y position.
    static float POSITION_Z = 3.0;      // Camera z position.

    /// Direction.

    static float lx = 0.0f;
    static float ly = 0.0f;
    static float lz = -1.0f;
}
#endif
