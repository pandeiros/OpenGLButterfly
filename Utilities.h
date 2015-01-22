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
    static float SPEED = 8.f;

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

// Bezier curve parameters.
namespace Bezier {

#define CTRL_POINTS 5
#define MIN_BEZIER_PREC 0

    // How many vertexes in a curve.
    static unsigned int BEZIER_PRECISION = 10;

    // Control points for lower right wing (left is symmetrical).
    static float lowerCtrlPoints[CTRL_POINTS][3] = {
        {0.f, 0.f, 2.f},
        {10.f, 0.f, 30.f},
        {30.f, 0.f, 0.f},
        {1.f, 0.f, 0.f}
    };

    // Control points for upper right wing (left is symmetrical).
    static float upperCtrlPoints[CTRL_POINTS][3] = {
        {0.f, 0.f, 1.f},
        {30.f, 0.f, 0.f},
        {30.f, 0.f, -30.f},
        {0.f, 0.f, -12.f}
    };

    int factorial (int n) {
        return (n == 1 || n == 0) ? 1 : factorial (n - 1) * n;
    }

    float fBernstein (unsigned int i, float t) {
        return (factorial (CTRL_POINTS-1) * std::pow (t, i) * std::pow (1 - t, CTRL_POINTS-1 - i) / factorial (i) / factorial (CTRL_POINTS-1 - i));
    }

    // Calculates points for a curve.
    float getBezierPoint (bool lower, bool left, float t, unsigned int coord) {
        float point = 0.f;

        for (unsigned int i = 0; i < CTRL_POINTS-1; ++i) {
            if (lower && left)
                point += lowerCtrlPoints[i][coord] * fBernstein (i, t);
            else if (!lower && left)
                point += upperCtrlPoints[i][coord] * fBernstein (i, t);
            else if (lower && !left)
                point += lowerCtrlPoints[i][coord] * (coord == 0 ? -1 : 1) * fBernstein (i, t);
            else
                point += upperCtrlPoints[i][coord] * (coord == 0 ? -1 : 1) * fBernstein (i, t);
        }

        return point;
    }


}
#endif
