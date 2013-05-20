// Copyright 2007 Scott Lanham
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

#include "graphAction.h"

namespace stk
{

graphAction::~graphAction()
{
}

graphAction::graphAction( bool cloneOnDescend, bool singleThread )
    : clone_on_descend( cloneOnDescend ), single_thread( singleThread )
{
    //! @param cloneOnDescend Clone this action to descend into child nodes of current node being acted upon.
    
    is_active = true;
}

void graphAction::apply ( graphNode::sptr node )
{
    //! @param node Node to apply action to.

    graphNode::nodeInfo info( node, graphNode::sptr(), graphEdge::sptr() );

    apply( info );
}

void graphAction::apply ( graphNode::nodeInfo info )
{
    //! @param info Information on node to apply action to.

    //! @par Notes
    //! State is accumulated in turn across the siblings but can be isolated or accumulated
    //! when a child processes it's own children.
    //!
    //!    Parent
    //!      |
    //!      |
    //!    Children --- Isolated or Accumulated ---> Children
    //!      |
    //!      |
    //!      V
    //!    Accumulated
    
    process( info, DESCEND );

    if ( is_active ) // Only allow action to descend to children if the action is still active.
    {
        graphEdge::listSptr edgeList = info.node() -> getEdgeList();

        graphEdge::sptr edge = edgeList -> first();

        graphAction* childAction;

        if ( clone_on_descend )
            childAction = clone(); // Clone action to isolate the childrens state changes.
        else
            childAction = this;

        while ( ! edge.isNull() && is_active )
        {
            if ( edge -> canTraverse( typeBits() ) )
            {
                //! @todo Multi threaded edge traversal. This is where the thread would be created.
                // if ( ! single_thread ) ...
                
                graphNode::nodeInfo childNodeInfo( edge -> link(), info.node(), edge );

                childAction -> apply( childNodeInfo ); // Action's "process" function must be re-entrant.
            }
            
            edge  = edgeList -> next();
        }

        if ( clone_on_descend ) delete childAction;
    }

    process( info, ASCEND );
}

int graphAction::type()
{
    return _type();
}

actionTypeBitField graphAction::typeBits()
{
    int typeVal = type();

    return typeBits( typeVal );
}

actionTypeBitField graphAction::typeBits ( int actionType )
{
    actionTypeBitField retVal( 1 );

    retVal << actionType;

    return retVal;
}

bool graphAction::active()
{
    return is_active;
}

void graphAction::active ( bool yesNo )
{
    is_active = yesNo;
}

}
