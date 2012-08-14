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

#include "findGraphAction.h"
#include "graphUtil.h"
#include "NodeNotFound.h"

namespace stk
{

graphNode::nodeInfo findNodeFromEdgeId ( graphNode::sptr graphRoot, long edgeId )
{
    //! @param graphRoot Root of graph to process.
    //! @param edgeId Edge ID of edge that links to node to find.
    //! @return nodeInfo struct with found node details.
    //! @throw NodeNotFound If node is not found.

    findGraphAction action ( edgeId );

    action.apply( graphRoot );

    graphNode::sptr ptr = action.nodeFound();

    if ( ptr.isNull() ) throw NodeNotFound( edgeId );

    graphNode::nodeInfo foundNodeInfo = action.nodeFoundInfo();

    return foundNodeInfo;
}

graphNode::sptr findNodeFromId ( graphNode::sptr graphRoot, long nodeId )
{
    //! @param graphRoot Root of graph to process.
    //! @param nodeId Id of node to find.
    //! @return Safe pointer to found node.
    //! @throw NodeNotFound If node is not found.

    findGraphAction action;

    action.findNodeFromNodeId( nodeId );

    action.apply( graphRoot );

    graphNode::sptr ptr = action.nodeFound();

    if ( ptr.isNull() ) throw NodeNotFound();

    return ptr;
}

graphNode::sptr findNodeFromName ( graphNode::sptr graphRoot, const string& nodeName )
{
    //! @param graphRoot Root of graph to process.
    //! @param nodeName Name of node to find.
    //! @return Safe pointer to found node.
    //! @throw NodeNotFound If node is not found.

    findGraphAction action ( nodeName );

    action.apply( graphRoot );

    graphNode::sptr ptr = action.nodeFound();

    if ( ptr.isNull() ) throw NodeNotFound( nodeName );

    return ptr;
}

void moveNode ( graphNode::sptr graphRoot, long nodeToMoveEdgeId, long newParentId, int newIndex )
{
    //! @param graphRoot Root of graph to process.
    //! @param nodeToMoveEdgeId The ID of the Edge that links to the node to move.
    //! @param newParentId The ID of the parent to link the node to.
    //!                    Use -1 if the root node is the new parent.
    //! @param newIndex Child index to move node to.
    //! @throw NodeNotFound If any node is not found.
    
    // Find old parent of node to move.

    graphNode::nodeInfo info = findNodeFromEdgeId( graphRoot, nodeToMoveEdgeId );

    // Find new parent of node to move.

    graphNode::sptr newParent;

    if ( newParentId > -1 )
    {
        newParent = findNodeFromId( graphRoot, newParentId );
    }

    // Remove node from current parent.

    if ( ! info.parent().isNull() )
    {
        info.parent() -> removeChild( info.edge() -> id() );
    }

    // Add node to new parent.

    if ( ! newParent.isNull() )
    {
        newParent -> insertChild( info.node(), newIndex, (info.edge()) -> name() );
    }
    else
        graphRoot -> addChild( info.node() );
}

}

