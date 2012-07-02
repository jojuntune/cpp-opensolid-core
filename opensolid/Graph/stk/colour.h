// Copyright 2004 Scott Lanham
// ---------------------------
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.

#ifndef COLOUR_H
#define COLOUR_H

#include <qgl.h>

//! Representation of a colour.

namespace stk
{

class colour
{
    public:
    
        colour();
        colour ( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha );
        
        GLfloat* array(); //!< Return pointer to colour components array.
        
        //! Set colour component values.
        void components ( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha );
        
        //! Get colour component values.
        void components ( GLfloat* red, GLfloat* green, GLfloat* blue, GLfloat* alpha ) const;
        
        bool isValid(); //!< Colour is valid if the alpha component is not zero.
        
    protected:    
    
        GLfloat      _components [ 4 ];
};

} // End namespace stk.

#endif

