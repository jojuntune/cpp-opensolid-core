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

#ifndef OS_MODELVIEW_H
#define OS_MODELVIEW_H

#include <QtGui/QWidget>
#include <QtGui/QMouseEvent>

#include <QtOpenGL/QGLFormat>
#include <QtOpenGL/QGLWidget>

#include "cameraModelView.h"
#include "renderTarget.h"

using namespace opensolid;

#include <stk/colour.h>
#include <stk/glMaterial.h>

using namespace stk;

//! Model view widget.

class modelView : public QGLWidget
{
    Q_OBJECT

    public:

        ~modelView();
        modelView ( QWidget* parent = 0 );

        void toggleOrthoMode ( bool on );

        void refresh();
        void refresh ( renderTarget::sptr rTarget ); //!< Clear and render modelview.

    protected:

        void initializeGL();
        void resizeGL ( int width, int height );
        void paintGL();

        void mouseMoveEvent ( QMouseEvent* event );
        void mousePressEvent ( QMouseEvent* event );
        //void wheelEvent ( QWheelEvent* event );

        void drawAxis();

    private:

        cameraModelView mvCamera;

        colour          bgColour; // Background colour.

        int             mouse_x;  // Last mouse x coordinate. Relative to the widget.
        int             mouse_y;  // Last mouse y coordinate. Relative to the widget.

        int             view_width;
        int             view_height;

        renderTarget::sptr  render_target;
};

#endif
