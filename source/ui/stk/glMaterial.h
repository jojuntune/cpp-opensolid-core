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

#ifndef GL_MATERIAL_H
#define GL_MATERIAL_H

#include "colour.h"

namespace stk
{

class glMaterial
{
    public:

        glMaterial();

        void ambient ( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha );  // Set
        void ambient ( colour& );  // Set.
        GLfloat* ambient();  // Get
        void ambient ( GLfloat* red, GLfloat* green, GLfloat* blue, GLfloat* alpha );  // Get

        void diffuse ( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha );  // Set
        void diffuse ( colour& );
        GLfloat* diffuse();  // Get
        void diffuse ( GLfloat* red, GLfloat* green, GLfloat* blue, GLfloat* alpha );  // Get

        void specular ( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha );  // Set
        void specular ( colour& );
        GLfloat* specular();  // Get
        void specular ( GLfloat* red, GLfloat* green, GLfloat* blue, GLfloat* alpha );  // Get

        void emission ( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha );  // Set
        void emission ( colour& );
        GLfloat* emission();  // Get
        void emission ( GLfloat* red, GLfloat* green, GLfloat* blue, GLfloat* alpha );  // Get

        void shininess ( GLfloat val );
        GLfloat shininess();

        void baseColour ( colour& );
        colour& baseColour();

        void setupGL();

        // Public Data. Needed for speedup of rendering.

        GLfloat      lightAmbient[4];   // Ambient component.
        GLfloat      lightDiffuse[4];   // Diffuse component.
        GLfloat      lightSpecular[4];  // Specular component.
        GLfloat      lightEmission[4];  // Emissive component.

        GLfloat      lightShininess; // Specular shininess component.

        colour      base_colour;  // Colour used if lighting is off.
};

}

#endif



