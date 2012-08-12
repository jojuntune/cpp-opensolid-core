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

#include "findGraphAction.h"

namespace stk
{

findGraphAction::findGraphAction()
    : graphAction( false )
{
    active( false );
    find_type = -1;
}

findGraphAction::findGraphAction ( long edgeId )
    : graphAction( false )
{
    findNodeFromEdgeId ( edgeId );
}

findGraphAction::findGraphAction ( const string& nodeName )
    : graphAction( false )
{
    findNodeFromName( nodeName );
}

findGraphAction* findGraphAction::clone()
{
    return new findGraphAction( *this );
}

void findGraphAction::clear()
{
    node_found_info = graphNode::nodeInfo();
}

void findGraphAction::findNodeFromEdgeId ( long edgeId )
{
    edge_id_toFind = edgeId;
    
    clear();
    
    find_type = EDGE_ID;
    active( true );
}

void findGraphAction::findNodeFromNodeId ( long nodeId )
{
    node_id_toFind = nodeId;
    
    clear();
    
    find_type = NODE_ID;
    active( true );
}

void findGraphAction::findNodeFromName ( const string& nodeName )
{
    node_name_toFind = nodeName;
    
    clear();
    
    find_type = NODE_NAME;
    active( true );
}

void findGraphAction::process ( graphNode::nodeInfo& info, int traversalType )
{
    //! @param info Information about node to process.
    //! @param traversalType Type of graph traversal.
    
    if ( traversalType == ASCEND ) return;
    
    switch ( find_type )
    {
        case EDGE_ID:
            findNodeFromEdgeId( info );
            break;

        case NODE_ID:
            findNodeFromNodeId( info );
            break;

        case NODE_NAME:
            findNodeFromName( info );
            break;
    }
}

void findGraphAction::findNodeFromEdgeId ( graphNode::nodeInfo& info )
{
    graphEdge::sptr edge = info.edge();

    if ( edge.isNull() ) return;
    
    if ( edge -> id() == edge_id_toFind )
    {
        node_found_info = info;
        active ( false );  // Dont' waist time looking for other nodes.
    }    
}

void findGraphAction::findNodeFromNodeId ( graphNode::nodeInfo& info )
{
    graphNode::sptr node = info.node();

    if ( node.isNull() ) return;
    
    if ( node -> id() == node_id_toFind )
    {
        node_found_info = info;
        active ( false );
    }
}

void findGraphAction::findNodeFromName ( graphNode::nodeInfo& info )
{
    graphNode::sptr node = info.node();

    if ( node.isNull() ) return;
    
    if ( node -> hasName ( node_name_toFind ) )
    {
        node_found_info = info;
        active ( false );
    }
}

graphNode::sptr findGraphAction::nodeFound()
{
    return node_found_info.node();
}

graphNode::sptr findGraphAction::nodeFoundParent()
{
    return node_found_info.parent();
}

graphNode::nodeInfo findGraphAction::nodeFoundInfo()
{
    return node_found_info;
}

int findGraphAction::_type()
{
    return FIND_GRAPH_ACTION;
}

}
