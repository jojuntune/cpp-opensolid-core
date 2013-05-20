// Copyright 2007 Scott Lanham.
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

#include "modelView.h"

#include <iostream>
#include <cstdlib>

using namespace std;

#include <stk/glStippleLine.h>

modelView::~modelView()
{
}

modelView::modelView ( QWidget* parent )
    :   QGLWidget ( parent )
{
    bgColour.components ( 1.0, 1.0, 1.0, 1.0 ); // Default to a white background.
}

void modelView::toggleOrthoMode ( bool on )
{
    if ( on )
    {
        mvCamera.viewType( camera::ORTHOGRAPHIC );
    }
    else
    {
        mvCamera.viewType( camera::PERSPECTIVE );
    }

    updateGL();
}

void modelView::refresh()
{
    updateGL();
}

void modelView::refresh ( renderTarget::sptr rTarget )
{
    render_target = rTarget;
    updateGL();
}

void modelView::initializeGL()
{
    // Overrides base class.
}

void modelView::resizeGL ( int width, int height )
{
    // Overrides base class.

    
    mvCamera.viewPortWidth( width );
    mvCamera.viewPortHeight( height );

    view_width = width;
    view_height = height;
}

void modelView::paintGL()
{
    // Clear framebuffer.

    GLfloat red, green, blue, alpha;

    bgColour.components( &red, &green, &blue, &alpha );
    
    glClearColor( red, green, blue, alpha );

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    // Setup camera.

    mvCamera.viewSetup();

    // Render axis'.

    drawAxis();

    // Invoke render target.

    if ( ! render_target.isNull() )
        render_target -> render();
}

void modelView::mouseMoveEvent ( QMouseEvent* event )
{
    int mov_x = event -> x() - mouse_x;
    int mov_y = event -> y() - mouse_y;

    mvCamera.roll ( mouse_x, mouse_y, mov_x, mov_y, 1.0 );

    mouse_x = event -> x();
    mouse_y = event -> y();

    updateGL();
}

void modelView::mousePressEvent ( QMouseEvent* event )
{
    mouse_x = event -> x();
    mouse_y = event -> y();
}

void modelView::drawAxis()
{
    colour axisColourX( 1.0, 0.0, 0.0, 1.0 );
    colour axisColourY( 0.0, 1.0, 0.0, 1.0 );
    colour axisColourZ( 0.0, 0.0, 1.0, 1.0 );

    double volSizeX = 2.0;
    double volSizeY = 2.0;
    double volSizeZ = 2.0;

    bool lightsOn = ( glIsEnabled( GL_LIGHTING ) == GL_TRUE );  // Save lighting state.

    glDisable( GL_LIGHTING );

    point origin ( 0.0, 0.0, 0.0, 1.0 );

    // +ve X axis.

    glMaterial lineMat;
    lineMat.baseColour( axisColourX );

    lineMat.setupGL();

    point extent( volSizeX / 2.0, 0.0, 0.0, 1.0 );

    glStippleLine axisLine( origin, extent );

    lineMat.setupGL();

    axisLine.render();

    // -ve X axis.

    axisLine.endPoint().x( volSizeX / - 2.0 );

    axisLine.stippleFactor = 3;
    axisLine.stipplePattern = 0xAAAA;

    axisLine.render();

    // +ve Y axis.

    lineMat.baseColour( axisColourY );
    axisLine.endPoint().components( 0.0, volSizeY / 2.0, 0.0, 1.0 );
    axisLine.stippleFactor = 0;

    lineMat.setupGL();

    axisLine.render();

    // -ve Y axis.

    axisLine.endPoint().y( volSizeY / - 2.0 );

    axisLine.stippleFactor = 3;

    axisLine.render();

    // +ve Z axis.

    lineMat.baseColour( axisColourZ );
    axisLine.endPoint().components( 0.0, 0.0, volSizeZ / 2.0, 1.0 );
    axisLine.stippleFactor = 0;

    lineMat.setupGL();

    axisLine.render();

    // -ve Z axis.

    axisLine.endPoint().z( volSizeZ / - 2.0 );

    axisLine.stippleFactor = 3;

    axisLine.render();

    if ( lightsOn ) glEnable( GL_LIGHTING );  // Restore lighting state.
}

