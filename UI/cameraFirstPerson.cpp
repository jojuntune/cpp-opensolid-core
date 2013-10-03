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

#include "cameraFirstPerson.h"
#include <stk/transform.h>

#include <cmath>

using namespace std;

cameraFirstPerson::cameraFirstPerson()
{    
    init();
}

void cameraFirstPerson::init()
{
    // Initialise object.
    // ------------------
              
    camera_type = camera::FIRST_PERSON;
    
    // Set default position, direction and rotation of camera.
    
    posn.components ( 5.0, 1.70, 5.0, 1.0 );
    
    forwardDirn.components ( - 1.0, 0.0, - 1.0 );

    upDirn.components ( 0.0, 1.0, 0.0 );
    
    adjustUpDirnError();
}

void cameraFirstPerson::viewSetup()
{
    //! @par Notes Transforms applied to matrices first apply to scene last.
    
    // Generate modelView transformation.
    
    stk::transform modelview;
    
    // Align coordinate system of camera to world. ie Camera looks down z axis.

    vector3 alignToVect;
    alignToVect.components ( 0.0, 0.0, - 1.0 );

    modelview.align ( forwardDirn, alignToVect );
    
    // Align cameras up direction with y axis.
    
    vector3 tmpUpDirn ( upDirn );
    modelview.apply ( tmpUpDirn );
    
    alignToVect.components ( 0.0, 1.0, 0.0 );
    
    modelview.align ( tmpUpDirn, alignToVect, true );  // Must be applied after z axis alignment.
    
    // Move camera to origin.
    
    modelview.translate ( - posn.x(), - posn.y(), - posn.z() );    
    
    // Multiply modelview matrix.
    
    glMatrixMode ( GL_MODELVIEW );
    glMultMatrixd ( modelview.elements() );

    // Invoke base camera view setup.
    
    camera::viewSetup();
}

void cameraFirstPerson::adjustUpDirnError()
{
    //! @par Notes   This is necessary to combat accumulative error.

    // Get angle to rotate through.
    double rotAngle = upDirn.angle ( forwardDirn );
    
    rotAngle -= M_PI / 2.0;
    
    // Generate normal to both vectors.
    vector3 normal;
    normal.crossProduct ( upDirn, forwardDirn );    
    
    stk::transform tmpTransform;
        
    // Rotate about normal.
    if ( ( rotAngle != 0.0 ) && ( ! normal.isNull() ) )
        tmpTransform.rotate ( rotAngle, posn, normal );
        
    // Apply transform.
    tmpTransform.apply ( upDirn );
}

void cameraFirstPerson::pan ( double angle )
{
    //! @param angle Angle to pan by.
    
    stk::transform transf;
    
    transf.rotateY ( angle );
    
    transf.apply ( forwardDirn );
    transf.apply ( upDirn );
    
    adjustUpDirnError();
}

void cameraFirstPerson::tilt ( double angle )
{
    //! @param angle Angle to tilt by.
    
    stk::transform transf;
    
    vector3 normal;
    normal.crossProduct ( upDirn, forwardDirn );
    
    point origin;
    
    transf.rotate ( angle, origin, normal );
    
    transf.apply ( forwardDirn );
    transf.apply ( upDirn );
    
    adjustUpDirnError();
}

void cameraFirstPerson::roll ( double angle )
{
    //! @param angle Angle to roll by.
 
    stk::transform transf;
    
    point origin;
    
    transf.rotate ( angle, origin, forwardDirn );    

    transf.apply ( upDirn );
    
    adjustUpDirnError();
}

void cameraFirstPerson::moveForward ( double distance )
{
    //! @param distance Distance to move forward by.
    
    // Project onto the X-Z plane.
    
    vector3 projected = forwardDirn;
    projected.projectXZ();
    
    // Turn into a unit vector.
    projected.normalise();
    
    // Multiply vector by distance to travel.
    projected *= distance;
    
    // Translate camera's position by adding the  projected vector to it.
    posn += projected;
}

void cameraFirstPerson::moveSideways ( double distance )
{
    //! @param distance Distance to move sideways by.
    
    vector3 normal;
    
    normal.crossProduct ( upDirn, forwardDirn );
    
    normal.projectXZ();
    
    normal.normalise();
    
    normal *= distance;
    
    posn += normal;
}

void cameraFirstPerson::moveVertically ( double distance )
{
    //! @param distance Distance to move vertically by.
    
    posn.y ( posn.y() + distance );
}

void cameraFirstPerson::moveRotateY ( double angle )
{
    //! @param angle Angle to rotate about y by.
    
    stk::transform transf;
    
    transf.rotateY ( angle );
    
    point forwardPoint = posn;
    forwardPoint += forwardDirn;
    
    point upPoint = posn;
    upPoint += upDirn;
    
    transf.apply ( posn );
    transf.apply ( forwardPoint );
    transf.apply ( upPoint );
    
    forwardDirn.generate ( posn, forwardPoint );
    upDirn.generate ( posn, upPoint );
    
    adjustUpDirnError();    
}

void cameraFirstPerson::lookAt ( double x, double y, double z )
{
    //! @param x X coordinate of position to look at.
    //! @param y Y coordinate of position to look at.
    //! @param z Z coordinate of position to look at.

    point endPoint ( x, y, z );

    forwardDirn.generate ( posn, endPoint );
    forwardDirn.normalise();

    adjustUpDirnError();
}

