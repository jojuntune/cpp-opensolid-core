// Copyright 2008 Scott Lanham.
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

#ifndef GROUPNODE_H
#define GROUPNODE_H

#include <stk/safePtr.h>
using namespace stk;

#include "graphNode.h"

namespace opensolid
{

//! Generic node used for grouping child nodes.

class groupNode : public graphNode
{
    public:

        typedef safePtr<groupNode> sptr;
        typedef safePtr< ptrList<sptr> > listSptr;
    
        groupNode();
    
        groupNode ( const string& name );

        void init();

        virtual int type();
    
    protected:

};

}

#endif
