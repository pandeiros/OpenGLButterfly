#ifndef _UTILITIES_
#define _UTILITIES_

#include <string>
#include <iomanip>
#include <iostream>
#include "GLUT.H"
#include "windows.h"

#define PI  3.1415f
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define MAX(a,b) (((a) > (b)) ? (a) : (b))

// Main variables and functions.
namespace Main
{
    // Title
    static std::string TITLE = ">>> OpenGL Butterfly Project <<<";

    // Greeting messages.
    static std::string AUTHOR_INFO = " Author: Pawel Kaczyski\n Date: 23.01.2015\n Made at: Faculty of Electronics and Information Technology\n";
    static std::string CAMERA_MOVEMENT = " >> Use 'w', 's', 'a', 'd' to zoom and move camera horizontally.\n >> Use up and down arrows to move camera verticaly.\n";
    static std::string LIGHT_INFO = " >> Use F1 and F2 to adjust light intensity.\n >> Use Page Up and Page Down to adjust Bezier curve complexity.\n";
    static std::string ANIM_INFO = " >> Hit Space to turn animation on/off.\n";

    // Prints formatted greeting message.
    static void printHeader()
    {
        unsigned int lineSize = 70;
        std::cout << std::setw(lineSize) << std::setfill('=') << "\n";
        std::cout << "               " << TITLE << "\n";
        std::cout << std::setw(lineSize) << std::setfill('-') << "\n";
        std::cout << AUTHOR_INFO;
        std::cout << std::setw(lineSize) << std::setfill('-') << "\n";
        std::cout << CAMERA_MOVEMENT;
        std::cout << std::setw(lineSize) << std::setfill('-') << "\n";
        std::cout << LIGHT_INFO;
        std::cout << std::setw(lineSize) << std::setfill('-') << "\n";
        std::cout << ANIM_INFO;
        std::cout << std::setw(lineSize) << std::setfill('-') << "\n";
        std::cout << "\n                           HAVE FUN :D\n\n";
        std::cout << std::setw(lineSize) << std::setfill('=') << "\n";
    }
}

// Window parameters.
namespace Window
{
    // Position.
    enum Position
    {
        POSITION_X = 300,    // Window x position.
        POSITION_Y = 200    // Window y position.
    };

    // Size.
    enum Size
    {
        WIDTH = 900,    // Window width.
        HEIGHT = 500    // Window height.
    };

    // Window title.
#define TITLE "Butterfly"

    // Display mode.
#define MODE (GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA)

}

// Camera position and movement parameters.
namespace Camera
{
    /// Position.

    static float POSITION_X = 13.0f;      // Camera x position.
    static float POSITION_Y = 30.0f;     // Camera y position.
    static float POSITION_Z = -35.0f;      // Camera z position.
    static float DELTA_X = 0.0f;
    static float DELTA_Y = 0.0f;
    static float DELTA_Z = 0.0f;
    static float SPEED = 8.f;

    /// Direction.

    static float DIR_X = -0.5f;      // Camera x direction.
    static float DIR_Y = -0.5f;      // Camera y direction.
    static float DIR_Z = 1.0f;     // Camera z direction.

    /// Rotation

    static float ANGLE_X = -150.0f;    // Camera x rotation angle.
    static float ANGLE_Y = 40.f;    // Camera y rotation angle.
    static float DELTA_ANGLE_X = 0.0f;      // Camera delta x rotation.
    static float DELTA_ANGLE_Y = 0.0f;      // Camera delta y rotation.
    static float ROTATION_MODIFIER = 0.2f;  // Camera rotation speed modifier.

    // Distance to point (0, 0 ,0)
    static float DISTANCE = 0.0f;
}

// Light position, spot and intensity parameters.
namespace Light
{

    // Border values for linear attenuation.

#define MAX_LINEAR_ATT 0.1f
#define MIN_LINEAR_ATT 0.008f

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
namespace Bezier
{

#define CTRL_POINTS 5
#define MIN_BEZIER_PREC 0
#define MAX_BEZIER_PREC 50

    // How many vertexes in a curve.
    static int BEZIER_PRECISION = 10;

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

    // Control points for right antenna of the butterfly.
    static float antennaCtrlPoints[CTRL_POINTS][3] = {
        {0.3f, 0.f, -3.f},
        {0.5f, 2.f, -4.f},
        {0.3f, 2.f, -2.f},
        {0.0, 0.0, 0.0}
    };

    // Factorial function,
    int factorial(int n)
    {
        return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
    }

    // Bernstein base polynomial function.
    float fBernstein(unsigned int i, float t)
    {
        return (factorial(CTRL_POINTS - 1) * std::pow(t, i) * std::pow(1 - t, CTRL_POINTS - 1 - i) / factorial(i) / factorial(CTRL_POINTS - 1 - i));
    }

    // Calculates points for a curve.
    float getBezierPoint(bool isWing, bool lower, bool right, float t, unsigned int coord)
    {
        float point = 0.f;

        for (unsigned int i = 0; i < CTRL_POINTS - 1; ++i)
        {
            if (isWing)
            {
                if (lower && right)
                    point += lowerCtrlPoints[i][coord] * fBernstein(i, t);
                else if (!lower && right)
                    point += upperCtrlPoints[i][coord] * fBernstein(i, t);
                else if (lower && !right)
                    point += lowerCtrlPoints[i][coord] * (coord == 0 ? -1 : 1) * fBernstein(i, t);
                else
                    point += upperCtrlPoints[i][coord] * (coord == 0 ? -1 : 1) * fBernstein(i, t);
            }
            else
            {
                if (right)
                    point += antennaCtrlPoints[i][coord] * fBernstein(i, t);
                else
                    point += antennaCtrlPoints[i][coord] * (coord == 0 ? -1 : 1) * fBernstein(i, t);
            }
        }

        return point;
    }
}

// Animation controls.
namespace Animation
{

    // Static FPS
    static unsigned int FPS = 60;

    // Animation on/off control.
    static bool isAnimOn = false;

    // Current frame.
    static unsigned long frame = 0;

    // Time delta for measuring elapsed time
    static float dt = 0.f;

    // Wing frequency modifier.
    static float modifier = 1.5f;

    /// Position and wing inclinations.

    static float wingInclination = -PI / 2.f;
    static float bodyInclination = -PI;

    /// Clock's times.

    clock_t begin = 0;
    clock_t end = 0;
}
#endif
