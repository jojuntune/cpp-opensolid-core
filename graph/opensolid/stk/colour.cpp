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

#include "colour.h"

namespace stk
{

colour::colour()
{
    components ( 0.0, 0.0, 0.0, 0.0 );
}

colour::colour ( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha )
{
    components ( red, green, blue, alpha );
}

GLfloat* colour::array()
{
    //! @return Colour components array.
    
    return _components;
}
        
void colour::components ( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha )
{
    //! @param red Red component of colour.
    //! @param green Green component of colour.
    //! @param blue Blue component of colour.
    //! @param aplha Alpha component of colour.
    
    _components[ 0 ] = red;
    _components[ 1 ] = green;
    _components[ 2 ] = blue;
    _components[ 3 ] = alpha;
}

void colour::components ( GLfloat* red, GLfloat* green, GLfloat* blue, GLfloat* alpha ) const
{
    //! @param red Pointer to place red component of colour in.
    //! @param green Pointer to place reen component of colour in.
    //! @param blue Pointer to place blue component of colour in.
    //! @param aplha Pointer to place alpha component of colour in.
    
    *red = _components[ 0 ];
    *green = _components[ 1 ];
    *blue = _components[ 2 ];
    *alpha = _components[ 3 ];
}

bool colour::isValid()
{
    if ( _components[ 3 ] == 0.0 )
        return false;
        
    return true;
}

} // End namespace stk.
