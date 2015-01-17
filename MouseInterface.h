#ifndef _MOUSE_INTERFACE_
#define _MOUSE_INTERFACE_

#include "Utilities.h"

#define MOUSE_DRAG_BUTTON GLUT_LEFT_BUTTON

namespace Mouse {

    /// Mouse drag controls.

    static int DRAG_X = -1;     // X-axis mouse drag control.
    static int DRAG_Y = -1;     // Y-axis mouse drag control

    // Mouse dragging control function.
    void mouseMove (int x, int y)
    {
        // If mouse button is down (DRAG_X and DRAG_Y  != -1).
        if (DRAG_X >= 0 && DRAG_Y >= 0)
        {
            // Change rotation.
            Camera::DELTA_ANGLE_X = (x - DRAG_X) / 180.f * PI * Camera::ROTATION_MODIFIER;
            Camera::DELTA_ANGLE_Y = (y - DRAG_Y) / 180.f * PI * Camera::ROTATION_MODIFIER;

            // Change direction.
            Camera::DIR_X = sin (Camera::ANGLE_X + Camera::DELTA_ANGLE_X);
            Camera::DIR_Y = sin (Camera::ANGLE_Y - Camera::DELTA_ANGLE_Y);
            Camera::DIR_Z = -cos (Camera::ANGLE_X + Camera::DELTA_ANGLE_X);
        }
    }

    // Mouse button pressing handler.
    void mouseButton (int button, int state, int x, int y) {
        
        // Camera moving button.
        if (button == MOUSE_DRAG_BUTTON) 		
        {
            // Press action.
            if (state == GLUT_DOWN)				
            {                
                DRAG_X = x;
                DRAG_Y = y;
            }
            // Release action.
            else    // state == GLUT_UP		    			
            {
                Camera::ANGLE_X += Camera::DELTA_ANGLE_X;
                Camera::ANGLE_Y -= Camera::DELTA_ANGLE_Y;
                DRAG_X = -1;
                DRAG_Y = -1;
            }
        }
    }
}

#endif