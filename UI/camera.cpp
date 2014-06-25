// Copyright 2004 Scott Lanham.
// ----------------------------
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.

#include "camera.h"
#include <stk/point.h>
#include <stk/transform.h>

#include <cmath>

using namespace std;

camera::~camera()
{
}

camera::camera()
{    
    init();
}

void camera::init()
{
    // Initialise object.
    // ------------------

    camera_type = BASE_CAMERA;

    view_type = PERSPECTIVE;

    // Set default geometry.
    
    focalLen = 0.75;
    view_port_width = 100;
    view_port_height = 100;
    dot_pitch = 0.25 / 1000.0;  // Must be in metres.
    
    // Set near and far clipping plane defaults.
    
    near_clip = 0.0;
    far_clip = 100.0;
}

void camera::viewSetup()
{
    //! @par Notes Transforms applied to matrices first apply to scene last.

    // Setup viewport dimensions.
    glViewport ( 0, 0, view_port_width, view_port_height );
    
    // *** Generate projection transformation.

    double top = ((( (double) ( view_port_height ) / 2.0 ) * ( dot_pitch ) )
                 / focalLen ) * ( near_clip + focalLen );
                 
    double bottom = -top;

    double right = ((( (double ) ( view_port_width ) / 2.0 ) * ( dot_pitch ) )
                   / focalLen ) * ( near_clip + focalLen );
                
    double left = - right;

    glMatrixMode ( GL_PROJECTION );

    if ( view_type == PERSPECTIVE )
        glFrustum ( left, right, bottom, top, near_clip + focalLen, far_clip + focalLen );
    else
        glOrtho ( left, right, bottom, top, near_clip + focalLen, far_clip + focalLen );

    glMatrixMode ( GL_MODELVIEW );  // Always default to modelview.
}

int camera::type()
{
    //! @return Type of camera.

    return camera_type;
}

void camera::viewType ( int type )
{
    view_type = type;
}

void camera::zoom ( double delta )
{
    //! @param delta Amount to change focal distance by.
 
    focalLen += delta;
    
    if ( focalLen < 0.001 ) focalLen = 0.001;
}

void camera::adjustOrthogonal ( vector3& vector1, vector3& vector2 )
{
    //! @param vector1 Reference vector.
    //! @param vector2 Vector to adjust to be orthogonal to the reference vector, vector1.
    
    // Get angle to rotate through.
    double rotAngle = vector2.angle ( vector1 );
    
    rotAngle -= M_PI / 2.0;
    
    // Generate normal to both vectors.
    vector3 normal;
    normal.crossProduct ( vector2, vector1 );
    
    stk::transform tmpTransform;
        
    // Rotate about normal.

    point origin ( 0.0, 0.0, 0.0 );
    
    if ( ( rotAngle != 0.0 ) && ( ! normal.isNull() ) )
        tmpTransform.rotate ( rotAngle, origin, normal );
        
    // Apply transform.
    // Transforms can only be applied to homogeneous points.
    
    tmpTransform.apply ( vector2 );
}

int camera::viewPortWidth()
{
    return view_port_width;
}

void camera::viewPortWidth ( int width )
{
    //! @param width Width of view port.

    view_port_width = width;
}

int camera::viewPortHeight()
{
    return view_port_height;
}

void camera::viewPortHeight ( int height )
{
    //! @param height Height of view port.

    view_port_height = height;
}

double camera::dotPitch()
{
    return dot_pitch;
}

void camera::dotPitch ( double size )
{
    //! @param size Size of dot pitch.

    dot_pitch = size;
}

double camera::focalLength()
{
    return focalLen;
}

void camera::focalLength ( double length )
{
    //! @param length Focal length to set.
    
    focalLen = length;
}

double camera::nearClip()
{
    return near_clip;
}

void camera::nearClip ( double distFromEye )
{
    //! @param distFromEye Distance of near clip plane from eye.
    near_clip = distFromEye;
}

double camera::farClip()
{
    return far_clip;
}

void camera::farClip ( double distFromEye )
{
    //! @param distFromEye Distance of far clip plane from eye.

    far_clip = distFromEye;
}
