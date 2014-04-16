// Copyright 2007 Scott Lanham.
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

#ifndef ASSEMBLY_NODE_H
#define ASSEMBLY_NODE_H

#include <stk/ptrList.h>
using namespace stk;

#include "graphNode.h"

namespace opensolid
{

class assemblyNode : public graphNode
{
    public:
    
        assemblyNode();
        virtual ~assemblyNode();
        
        assemblyNode ( const string& assemblyName );
    
    private:
        
};

}

#endif
