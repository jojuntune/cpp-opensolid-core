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

#ifndef GL_STIPPLELINE_H
#define GL_STIPPLELINE_H

#include "glLine.h"
#include "point.h"

namespace stk
{

class glStippleLine : public glLine
{
    public:
    
        glStippleLine ( point& start, point& end, bool useNormals = false );
        
        virtual void render();
    
        int             stippleFactor;
        unsigned short  stipplePattern;
};

}

#endif
