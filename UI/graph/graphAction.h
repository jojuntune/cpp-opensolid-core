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

#ifndef GRAPH_ACTION_H
#define GRAPH_ACTION_H

#include <stk/graphAction.h>
using namespace stk;

#include "graphNode.h"

namespace opensolid
{

class graphAction : public stk::graphAction
{
    public:

        //! Action types.

        enum
        {
            LIST_GRAPH_ACTION,
            EVALUATE_GRAPH_ACTION,
            RENDER_GRAPH_ACTION
        };

        virtual int type();
    
    protected:

        virtual ~graphAction();

        graphAction ( bool cloneOnDescend, bool singleThread = false );

        //! Convert processing of stk graphNode into processing of opensolid graphNode.
        void process ( stk::graphNode::nodeInfo& info, int traversalType );
        
        //! Apply action to opensolid graph node.
        virtual void process ( opensolid::graphNode::nodeInfo& info, int traversalType ) = 0;
};

}

#endif
