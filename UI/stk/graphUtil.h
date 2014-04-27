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

#ifndef STK_GRAPHUTIL_H
#define STK_GRAPHUTIL_H

#include "graphEdge.h"
#include "graphNode.h"

namespace stk
{
    //! Utility functions to manipulate graph.
        
    //! Find node within graph given its edge (link) ID.
    graphNode::nodeInfo findNodeFromEdgeId ( graphNode::sptr graphRoot, long edgeId );
    
    //! Find node within graph given its node ID.
    graphNode::sptr findNodeFromId ( graphNode::sptr graphRoot, long nodeId );
    
    //! Find node within graph given its name.
    graphNode::sptr findNodeFromName ( graphNode::sptr graphRoot, const string& nodeName );

    //! Move a node within graph.
    void moveNode ( graphNode::sptr graphRoot, long nodeToMoveEdgeId, long newParentId, int newIndex );
}

#endif

