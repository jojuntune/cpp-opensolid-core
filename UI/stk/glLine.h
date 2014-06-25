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

#ifndef GL_LINE_H
#define GL_LINE_H

#include "point.h"
#include "vector3.h"

namespace stk
{

class glLine
{
    public:
    
        glLine ( bool useNormals = false );
        
        virtual ~glLine();
        
        glLine ( point& start, point& end, bool useNormals = false );
        
        void startPoint ( point& point );
        point& startPoint();
        
        void endPoint ( point& point );
        point& endPoint();
        
        void startNormal ( vector3& normal );
        vector3& startNormal();
        
        void endNormal ( vector3& normal );
        vector3& endNormal();
        
        void lineWidth ( double width );
        double lineWidth();        
      
        virtual void render();
        
    protected:                    
    
        point      startPt;
        point      endPt;
        
        vector3     startNorm;
        vector3     endNorm;
        
        bool        useNorms;  // If true, use normals.
        
        double      line_width;
};

}

#endif
