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

#ifndef NODENOTFOUND_H
#define NODENOTFOUND_H

#include "Exception.h"
#include "safePtr.h"

namespace stk
{
    //! Exception thrown when a specified node is not found.

    class NodeNotFound : public Exception
    {
        public:

            NodeNotFound();
            NodeNotFound( long edgeId );
            NodeNotFound( const string& name );

            long edgeId;
            string nodeName;
    };
}

#endif
