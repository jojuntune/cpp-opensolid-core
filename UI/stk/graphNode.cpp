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

#include "findGraphAction.h"
#include "graphNode.h"

namespace stk
{

graphNode::~graphNode()
{
}

void graphNode::init()
{
}

graphNode::graphNode()
{
    init();
}

graphNode::graphNode ( const string& name )
    : namedObject( name )
{
    init();
}

graphNode::graphNode ( graphNode& copyFrom )
    : namedObject(), uniqueObject()
{
    init();
    copy ( copyFrom );
}

graphNode& graphNode::operator= ( graphNode& copyFrom )
{
    if ( this == &copyFrom ) return *this; // No self assignment.

    copy ( copyFrom );

    return *this;
}

graphEdge::sptr graphNode::addChild ( sptr node, const string& linkName )
{
    //! @param node Node to add as child.
    //! @param linkName Name of the link to the child node.
    //! @return Edge to added child.
    //! @throw NotPermitted If operation is not permitted.

    if ( node == this ) throw NotPermitted(); // Can't self link. Would cause infinite recursion.

    graphEdge::sptr* edge = new graphEdge::sptr( new graphEdge ( linkName, node ) );

    graphEdge::sptr retEdge = edge; // For thread safety.

    { THREAD_SYNC children.append ( edge, true ); }

    return retEdge;
}

graphEdge::sptr graphNode::addChild ( sptr node, int index, const string& linkName )
{
    //! @param node Node to add as child.
    //! @param index Index of position to place child node in. Use -1 to append to end of children.
    //! @param linkName Name of the link to the child node.
    //! @return Edge to added child.
    //! @throw NotPermitted If operation is not permitted.
    //! @par Note This is just a helper function so that the append/insert logic doesn't need to
    //!           be applied repeatedly at higher levels.

    if ( index == -1 )
        return addChild( node, linkName );
    else
        return insertChild( node, index, linkName );
}

graphEdge::sptr graphNode::insertChild ( sptr node, int index, const string& linkName )
{
    //! @param node Node to add as child.
    //! @param index Index to add child at.
    //! @param linkName Name of the link to the child node.
    //! @return Edge to inserted child.
    //! @throw NotPermitted If operation is not permitted.

    if ( node == this ) throw NotPermitted(); // Can't self link. Would cause infinite recursion.
    
    graphEdge::sptr* edge = new graphEdge::sptr( new graphEdge ( linkName, node ) );

    graphEdge::sptr retEdge = edge; // For thread safety.
    
    { THREAD_SYNC children.insert ( edge, index, true ); }

    return retEdge;
}

graphEdge::sptr graphNode::removeChild ( long edgeId )
{
    //! @param edgeId Id of edge to remove.
    //! @return Safe pointer to graph edge that was removed.

    graphEdge::sptr removedEdge;
    
    { THREAD_SYNC
    
        graphEdge::sptr* edge = findEdge( edgeId );
        
        if ( edge )
        {
            removedEdge = *edge;
            children.remove ( edge );
        }
        else
            throw EdgeNotFound( edgeId );
    }

    return removedEdge;
}

void graphNode::removeAllChildren()
{
    THREAD_SYNC
    children.clear();
}

void graphNode::moveChild ( int oldIndex, int newIndex )
{
    { THREAD_SYNC
    
        graphEdge::sptr* edge = children.atIndex( oldIndex );
        
        if ( edge )
        {
            children.move( oldIndex, newIndex );
        }
    }
}

int graphNode::childIndex ( long edgeId )
{
    //! @param edgeId Id of edge to find index of.
    //! @return List index (position) of child, -1 if child is not found. Index is 0 based.

    return findEdgeIndex ( edgeId );
}

bool graphNode::hasChild ( long edgeId )
{
    //! @param edgeId ID of edge that corresponds to child node.
    //! @return True if child node was found.

    graphEdge::sptr* edge;

    { THREAD_SYNC
    
        edge = findEdge( edgeId );
        if ( edge ) return true;
    }

    return false;
}

bool graphNode::hasChild ( long nodeId, int index )
{
    //! @param nodeId ID of child node to find.
    //! @param index Child index of node to find.
    //! @return True if child node was found.

    sptr node = childAtIndex ( index );

    if ( ! node.isNull() && node -> id() == nodeId ) return true;

    return false;
}

int graphNode::childCount()
{
    //! @return Number of children this node has.

    int childCount;

    { THREAD_SYNC childCount = children.count(); }

    return childCount;
}

graphNode::sptr graphNode::childAtIndex ( int index )
{
    //! @param index Index of child to return.
    //! @return Safe pointer to graph node that represents the found child node.
    
    sptr node;
    graphEdge::sptr* edge;

    { THREAD_SYNC
    
        edge = children.atIndex( index );
        if ( edge ) node = (*edge) -> link();
    }

    return node;
}

graphEdge::sptr graphNode::edgeAtIndex ( int index )
{
    //! @param index Index of edge to return.
    //! @return Safe pointer to graph edge.

    return children.atIndex( index );
}

graphNode::listSptr graphNode::getChildList()
{
    //! @return List of children of this node.

    listSptr retList = listSptr( new ptrList< sptr >() );

    { THREAD_SYNC
    
        graphEdge::sptr* edge = children.first();

        while ( edge )
        {
            retList -> append ( new sptr( (*edge) -> link() ), true );
            edge = children.next();
        }   
    }

    return retList;
}

graphEdge::listSptr graphNode::getEdgeList()
{
    //! @return List of edges that belong to this node.

    graphEdge::listSptr retList = graphEdge::listSptr( new ptrList< graphEdge::sptr >() );

    { THREAD_SYNC
    
        graphEdge::sptr* edge = children.first();

        while ( edge )
        {
            retList -> append ( new graphEdge::sptr( edge ), true );
            edge = children.next();
        }   
    }

    return retList;
}

// PRIVATE

void graphNode::copy ( graphNode& copyFrom )
{
    removeAllChildren();

    // Copy parent/child node relationships. Generate new edges.

    graphEdge::listSptr edgeList = copyFrom.getEdgeList();
    
    graphEdge::sptr edge = edgeList -> first();

    while ( ! edge.isNull() )
    {
        // Take a deep copy of the edge.
        { THREAD_SYNC children.append ( new graphEdge::sptr( edge, true ), true ); }
        
        edge = edgeList -> next();
    }

    name ( copyFrom.name() );
}

graphEdge::sptr* graphNode::findEdge ( long edgeId )
{
    //! @param edgeId Id of edge to find.
    //! @return Pointer to edge that was found otherwise null.
    //! @par Notes
    //!            Calling function must do it's own thread sync.
    
    graphEdge::sptr* edge;

    edge = children.first();

    while ( edge )
    {
        if ( (*edge) -> id() == edgeId )
            break;

        edge = children.next();
    }

    return edge;
}

int graphNode::findEdgeIndex ( long edgeId )
{
    //! @param edgeId Id of edge to find index of.
    
    int index = 0;

    graphEdge::sptr* edge;

    { THREAD_SYNC
    
        edge = children.first();

        while ( edge )
        {
            if ( (*edge) -> id() == edgeId )
                break;
            
            edge = children.next();

            index ++;
        }
    }

    if ( edge )
        return index;
    else
        return -1;
}

} // Namespace stk.
