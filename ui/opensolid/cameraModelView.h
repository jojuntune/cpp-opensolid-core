// Copyright 2007 Scott A.E. Lanham
// --------------------------------
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.

#ifndef MODELVIEWCAMERA_H
#define MODELVIEWCAMERA_H

#include <qgl.h>

#include "camera.h"
#include <stk/vector3.h>

class cameraModelView : public camera
{
    public:
    
        cameraModelView();
        
        virtual void viewSetup();

        void rotateX ( double angle ); //!< Rotate model about eye X axis.
        void rotateY ( double angle ); //!< Rotate model about eye Y axis.
        void rotateZ ( double angle ); //!< Rotate model about eye Z axis.

        //! Roll model like a ball based on interaction with the viewport.
        void roll ( int viewGrabPosnX, int viewGrabPosnY, int movementX, int movementY, double sensitivity );

    protected:

    private:

        vector3 model_y_axis; //!< Models y axis in eye coordinates. Both axis are rooted at the origin.
        vector3 model_z_axis; //!< Models z axis in eye coordinates.

        void    init();

        double  step_back_dist; //!< Distance to step back in +ve Z direction from origin.

        double  pan_angle; //!< Look left or right.
        double  tilt_angle; //!< Look up and down.
};

#endif

