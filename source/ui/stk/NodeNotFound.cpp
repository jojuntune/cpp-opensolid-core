// Copyright 2008 Scott Lanham
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

#include "namedObject.h"

#include "NodeNotFound.h"

namespace stk
{
    NodeNotFound::NodeNotFound()
    {
        edgeId = -1;
    }
    
    NodeNotFound::NodeNotFound( long id )
    {
        //! @param id ID of edge that was not found.
        
        edgeId = id;
    }

    NodeNotFound::NodeNotFound( const string& name )
    {
        //! @param name Safe pointer to node name not found.
        
        nodeName = name;
    }
}

