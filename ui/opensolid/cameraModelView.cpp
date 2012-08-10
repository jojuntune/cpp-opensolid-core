// Copyright 2007 Scott A.E. Lanham, Australia.
// --------------------------------------------
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.

#include "cameraModelView.h"
#include <stk/transform.h>

cameraModelView::cameraModelView()
{
    camera_type = camera::MODELVIEW;

    init();
}

void cameraModelView::init()
{
    step_back_dist = 5.0;

    pan_angle = 0.0;
    tilt_angle = 0.0;

    model_y_axis.components ( 0.0, 1.0, 0.0 );
    model_z_axis.components ( 0.0, 0.0, 1.0 );
}

void cameraModelView::viewSetup()
{
    camera::viewSetup();

    stk::transform modelViewTransf;
    stk::transform cameraTransf;

    // Align Z axis to eye.

    vector3 axis ( 0.0, 0.0, 1.0 );
    modelViewTransf.align ( axis, model_z_axis );

    // Align Y axis to eye.

    axis.components ( 0.0, 1.0, 0.0 ); // Keep y axis orthogonal to z axis.
    modelViewTransf.apply ( axis );

    modelViewTransf.align ( axis, model_y_axis, true );

    // Setup camera position transform.

    cameraTransf.translate ( 0.0, 0.0, - step_back_dist );
    
    // Set OpenGL Modelview matrix.

    glMatrixMode ( GL_MODELVIEW );
    glMultMatrixd ( cameraTransf.elements() );
    glMultMatrixd ( modelViewTransf.elements() );
}

void cameraModelView::rotateX ( double angle )
{
    //! @param angle Angle, in radians, to rotate by.

    stk::transform transf;

    transf.rotateX ( angle );

    transf.apply ( model_y_axis );
    transf.apply ( model_z_axis );

    adjustOrthogonal ( model_z_axis, model_y_axis );

    model_y_axis.normalise();
    model_z_axis.normalise();
}

void cameraModelView::rotateY ( double angle )
{
    //! @param angle Angle, in radians, to rotate by.

    stk::transform transf;

    transf.rotateY ( angle );

    transf.apply ( model_y_axis );
    transf.apply ( model_z_axis );

    adjustOrthogonal ( model_z_axis, model_y_axis );

    model_y_axis.normalise();
    model_z_axis.normalise();
}

void cameraModelView::rotateZ ( double angle )
{
    //! @param angle Angle, in radians, to rotate by.

    stk::transform transf;

    transf.rotateZ ( angle );

    transf.apply ( model_y_axis );
    transf.apply ( model_z_axis );

    adjustOrthogonal ( model_z_axis, model_y_axis );

    model_y_axis.normalise();
    model_z_axis.normalise();
}

void cameraModelView::roll ( int viewGrabPosnX, int viewGrabPosnY, int movementX, int movementY, double sensitivity )
{
    //! @param viewGrabPosnX X coordinate of position viewport was grabbed at.
    //! @param viewGrabPosnY Y coordinate of position viewport was grabbed at.
    //! @param movementX X direction movement to use for magnitude and direction of rotations.
    //! @param movementY Y direction movement to use for magnitude and direction of rotations.
    //! @param sensitivity Rotation magnitude multiplier.
    //! @par Notes Viewport origin is in top left corner. Think of this function as rolling a ball in the centre
    //!            of the screen.

    int viewWidth = view_port_width;
    int viewHeight = view_port_height;

    int centreX = viewWidth / 2;
    int centreY = viewHeight / 2;

    int ballRadius = centreX > centreY ? centreY : centreX;

    int centreDeltaX = viewGrabPosnX - centreX;  // Deltas from the centre of the veiwport.
    int centreDeltaY = viewGrabPosnY - centreY;

    // Calculate rotational scaling factors. Based on distance from viewport centre.

    /* This code uses a "sqashed" ball. 
    double scaleFactX = (double)( centreDeltaX * centreDeltaX ) / (double)( centreX * centreX );
    double scaleFactY = (double)( centreDeltaY * centreDeltaY ) / (double)( centreY * centreY );
    */

    double scaleFactX = (double)( centreDeltaX * centreDeltaX ) / (double)( ballRadius * ballRadius );
    double scaleFactY = (double)( centreDeltaY * centreDeltaY ) / (double)( ballRadius * ballRadius );

    if ( scaleFactX > 1.0 ) scaleFactX = 1.0;
    if ( scaleFactY > 1.0 ) scaleFactY = 1.0;

    // Calculate Z rotation signs.

    double zRot_Xsign = ( viewGrabPosnY - centreY ) < 0.0 ? -1.0 : 1.0;
    double zRot_Ysign = ( viewGrabPosnX - centreX ) > 0.0 ? -1.0 : 1.0;

    // Calculate rotations.

    double rotX = ( (double)movementY / (double)centreX ) * ( 1.0 - scaleFactX );
    double rotY = ( (double)movementX / (double)centreX ) * ( 1.0 - scaleFactY );
    double rotZ = ( movementX * zRot_Xsign / centreY ) * scaleFactY;  // Rotation from top or bottom of viewport.
    rotZ += ( movementY * zRot_Ysign / centreY ) * scaleFactX;  // Rotation from left or right of viewport.

    rotX *= sensitivity;
    rotY *= sensitivity;
    rotZ *= sensitivity;

    // Apply to model position.

    stk::transform transf;

    transf.rotateX ( rotX );
    transf.rotateY ( rotY );
    transf.rotateZ ( rotZ );

    transf.apply ( model_y_axis );
    transf.apply ( model_z_axis );

    adjustOrthogonal ( model_z_axis, model_y_axis );

    model_y_axis.normalise();
    model_z_axis.normalise();
}


