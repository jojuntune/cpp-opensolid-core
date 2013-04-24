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

#include "glLine.h"

#include <qgl.h>

namespace stk
{

glLine::glLine ( bool useNormals )
{
    useNorms = useNormals;
    line_width = 1.0;
}

glLine::~glLine()
{
}

glLine::glLine ( point& start, point& end, bool useNormals )
{
    startPt = start;
    endPt = end;
    
    useNorms= useNormals;
    
    line_width = 1.0;
}

void glLine::startPoint ( point& point )
{
    startPt = point;
}

point& glLine::startPoint()
{
    return startPt;
}
        
void glLine::endPoint ( point& point )
{
    endPt = point;
}

point& glLine::endPoint()
{
    return endPt;
}

void glLine::startNormal ( vector3& normal )
{
    startNorm = normal;
}

vector3& glLine::startNormal()
{
    return startNorm;
}
        
void glLine::endNormal ( vector3& normal )
{
    endNorm = normal;
}

vector3& glLine::endNormal()
{
    return endNorm;
}

void glLine::lineWidth ( double width )
{
    line_width = width;
}

double glLine::lineWidth()
{
    return line_width;
}

void glLine::render()
{
    glLineWidth( line_width );
    
    glBegin ( GL_LINES );
        
        if ( useNorms )
            glNormal3dv ( startNorm.elements );
            
        glVertex4dv ( startPt.elements );
        
        if ( useNorms )
            glNormal3dv ( endNorm.elements );
            
        glVertex4dv ( endPt.elements );        
 
    glEnd();
}

} // namespace stk
