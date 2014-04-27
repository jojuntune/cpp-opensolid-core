// Copyright 2004 Scott A.E. Lanham.
// ---------------------------------
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.

#ifndef FIRSTPERSONCAMERA_H
#define FIRSTPERSONCAMERA_H

#include <qgl.h>

#include "camera.h"
#include <stk/point.h>
#include <stk/vector3.h>

//!@par Notes The camera is always in the same position in eye coordinates.

class cameraFirstPerson : public camera
{
    public:
    
        cameraFirstPerson();
        
        virtual void viewSetup(); //!< Construct modelview and projection matrices.
        
        void pan ( double angle ); //!< Rotate about cameras local y axis.
        void tilt ( double angle ); //!< Rotate about normal ( to forward and up directions ).
        void roll ( double angle ); //!< Rotate about the forward facing direction.
        
        //! Move camera forward in the XZ plane in the direction it is already facing.
        void moveForward ( double distance );
        //! Move camera sideways in the XZ plane normal to the up and forward directions.
        void moveSideways ( double distance );
        //! Move camera position vertically. ie In the Y direction.
        void moveVertically ( double distance );
        //! Rotate cameras position about y. Adjust forward vector.
        void moveRotateY ( double angle );  // Move about global y axis.

        void lookAt ( double x, double y, double z ); //!< Point camera at specific coordinates.

    protected:

    private:

        void init();
    
        void adjustUpDirnError(); //!< Adjust up vector to be perpendicular to the forward vector.
    
        point       posn;  // Camera position.
        vector3     forwardDirn;  // Camera axis in forward facing direction.
        vector3     upDirn;  // Vector perpendicular to forward that indicates the top of the camera.
};

#endif
