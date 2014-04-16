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

#ifndef FRAGMENT_NODE_H
#define FRAGMENT_NODE_H

#include <stk/safePtr.h>
using namespace stk;

#include "graphNode.h"

namespace opensolid
{

class fragmentNode : public graphNode
{
    public:

        typedef safePtr<fragmentNode> sptr;
        typedef safePtr< ptrList<sptr> > listSptr;
    
        fragmentNode();
    
        fragmentNode ( const string& fragmentName );

        void init();

        virtual int type();
    
    protected:

};

}

#endif
