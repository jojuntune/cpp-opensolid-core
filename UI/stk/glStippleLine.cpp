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

#include "glStippleLine.h"

#include <qgl.h>

namespace stk
{

glStippleLine::glStippleLine ( point& start, point& end, bool useNormals )
    : glLine ( start, end, useNormals )
{
    stippleFactor = 0;
}

void glStippleLine::render()
{
    if ( stippleFactor )
    {
        glLineStipple ( stippleFactor, stipplePattern );
        glEnable ( GL_LINE_STIPPLE );
    }
    else
        glDisable ( GL_LINE_STIPPLE );
        
    glLine::render();
    
    glDisable ( GL_LINE_STIPPLE );
}

}
