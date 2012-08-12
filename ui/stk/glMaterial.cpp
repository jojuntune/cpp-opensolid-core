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

#include "glMaterial.h"

namespace stk
{

glMaterial::glMaterial()
{
    lightAmbient [ 3 ] = 0.0;
    lightDiffuse [ 3 ] = 0.0;
    lightSpecular [ 3 ] = 0.0;
    lightEmission [ 3 ] = 0.0;
    lightShininess = 0.0;    
}

void glMaterial::ambient ( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha )
{
    lightAmbient [ 0 ] = red;
    lightAmbient [ 1 ] = green;
    lightAmbient [ 2 ] = blue;
    lightAmbient [ 3 ] = alpha;    
}

void glMaterial::ambient ( colour& ambientColour )
{
    GLfloat* colourArray = ambientColour.array();
    
    for ( int index = 0; index < 4; index ++ )
        lightAmbient [ index ] = colourArray [ index ];
}

GLfloat* glMaterial::ambient()
{
    return lightAmbient;
}

void glMaterial::ambient ( GLfloat* red, GLfloat* green, GLfloat* blue, GLfloat* alpha )
{
    *red = lightAmbient [ 0 ];
    *green = lightAmbient [ 1 ];
    *blue = lightAmbient [ 2 ];
    *alpha = lightAmbient [ 3 ];
}

void glMaterial::diffuse ( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha )
{
    lightDiffuse [ 0 ] = red;
    lightDiffuse [ 1 ] = green;
    lightDiffuse [ 2 ] = blue;
    lightDiffuse [ 3 ] = alpha;    
}

void glMaterial::diffuse ( colour& diffuseColour )
{
    GLfloat* colourArray = diffuseColour.array();

    for ( int index = 0; index < 4; index ++ )
        lightDiffuse [ index ] = colourArray [ index ];
}

GLfloat* glMaterial::diffuse()
{
    return lightDiffuse;
}

void glMaterial::diffuse ( GLfloat* red, GLfloat* green, GLfloat* blue, GLfloat* alpha )
{
    *red = lightDiffuse [ 0 ];
    *green = lightDiffuse [ 1 ];
    *blue = lightDiffuse [ 2 ];
    *alpha = lightDiffuse [ 3 ];
}

void glMaterial::specular ( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha )
{
    lightSpecular [ 0 ] = red;
    lightSpecular [ 1 ] = green;
    lightSpecular [ 2 ] = blue;
    lightSpecular [ 3 ] = alpha;    
}

void glMaterial::specular ( colour& specularColour )
{
    GLfloat* colourArray = specularColour.array();
    
    for ( int index = 0; index < 4; index ++ )
        lightSpecular [ index ] = colourArray [ index ];
}

GLfloat* glMaterial::specular()
{
    return lightSpecular;
}

void glMaterial::specular ( GLfloat* red, GLfloat* green, GLfloat* blue, GLfloat* alpha )
{
    *red = lightSpecular [ 0 ];
    *green = lightSpecular [ 1 ];
    *blue = lightSpecular [ 2 ];
    *alpha = lightSpecular [ 3 ];
}

void glMaterial::emission ( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha )
{
    lightEmission [ 0 ] = red;
    lightEmission [ 1 ] = green;
    lightEmission [ 2 ] = blue;
    lightEmission [ 3 ] = alpha;    
}

void glMaterial::emission ( colour& emissionColour )
{
    GLfloat* colourArray = emissionColour.array();
    
    for ( int index = 0; index < 4; index ++ )
        lightEmission [ index ] = colourArray [ index ];
}

GLfloat* glMaterial::emission()
{
    return lightEmission;
}

void glMaterial::emission ( GLfloat* red, GLfloat* green, GLfloat* blue, GLfloat* alpha )
{
    *red = lightEmission [ 0 ];
    *green = lightEmission [ 1 ];
    *blue = lightEmission [ 2 ];
    *alpha = lightEmission [ 3 ];
}

void glMaterial::shininess ( GLfloat val )
{
    lightShininess = val;
}

GLfloat glMaterial::shininess()
{
    return lightShininess;
}

void glMaterial::baseColour ( colour& colr )
{    
    base_colour = colr;
}

colour& glMaterial::baseColour()
{
    return base_colour;
}

void glMaterial::setupGL()
{
    // Send material through to opengl.
    // --------------------------------
    
    GLfloat params [ 4 ];
    
    // Ambient
    if ( lightAmbient [ 3 ] > 0.0 )
        glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, lightAmbient );

    // Diffuse
    if ( lightDiffuse[ 3 ] > 0.0 )
        glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, lightDiffuse );
    
    // Specular
    if ( lightSpecular[ 3 ] > 0.0 )
        glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, lightSpecular );
    
    // Shininess
    glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, lightShininess );

    // Emission
    if ( lightEmission[ 3 ] > 0.0 )
        glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, lightEmission );

    // Set non-lighting colour for non-lit cases.
    
    if ( base_colour.isValid() )
        glColor4fv( base_colour.array() );
    else
    {
        for ( int index = 0; index < 4; index ++ )        
            params[ index ] = lightAmbient[ index ] + lightDiffuse[ index ];
            
        glColor4fv( params );
    }
}

}
