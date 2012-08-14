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

#include <sstream>

#include <stk/dumpGraphAction.h>
#include <stk/graphUtil.h>
#include <stk/NameInUse.h>
#include <stk/NodeNotFound.h>

#include "componentNode.h"
#include "evaluateGraphAction.h"
#include "fragmentNode.h"
#include "groupNode.h"
#include "listGraphAction.h"
#include "paramNode.h"
#include "pointNode.h"
#include "project.h"
#include "projectEvents.h"
#include "renderGraphAction.h"

namespace opensolid
{

project::project ( const string& projectName )
    : namedObject( projectName )
{
    //! @param projectName New projects name.

    graph_root = graphNode::sptr( new groupNode( projectName ) );
}

void project::render()
{
    renderGraphAction action;

    action.apply( graph_root );
}

graphNode::nodeInfo project::findNodeFromEdgeId ( int edgeId )
{
    //! @param edgeId Id of edge to find node from.

    stk::graphNode::nodeInfo rootInfo = stk::findNodeFromEdgeId( graph_root, edgeId );

    return rootInfo;
}

graphNode::sptr project::findNode ( const string& nodeName )
{
    //! @param nodeName Name of node to find.

    return stk::findNodeFromName( graph_root, nodeName );
}

graphNode::sptr project::findNode ( int nodeId )
{
    //! @param nodeId ID of node to find.
    //! @throw NodeNotFound If node was not found.

    return stk::findNodeFromId( graph_root, nodeId );
}

graphNode::sptr project::graphRoot()
{
    return graph_root;
}

void project::evaluate()
{
    evaluateGraphAction action;

    action.apply( graph_root );

    fireEvent( projectGraphEvaluated() );
}

graphNode::nodeInfo project::addNewComponent ( const string& componentName, long parentId, int index )
{
    //! @param componentName Name of new component. Leave as empty string for auto name generation.
    //! @param parentId Id of parent to add fragment to as a child.
    //!                 Use -1 to add to graph root.
    //! @param index Index of position to place new component in. Use -1 to append to end of children.
    //! @return ID of Edge that links to newly created component.
    //! @throw NameInUse If name is already used within project.

    string compName;

    // Generate a name if none provided.
    
    if ( componentName.empty() )
    {
        compName = generate_next_name( "component", graph_root );
    }
    else
        compName = componentName;

    if ( nameInUse( graph_root, compName ) ) throw stk::NameInUse();

    // Find parent node.

    graphNode::sptr parent;

    if ( parentId > -1 )
    {
        parent = stk::findNodeFromId( graph_root, parentId );
    }
    else
        parent = graph_root;

    componentNode* component = new componentNode( compName );

    component -> addEventListener( this );
    
    fireEvent( projectChanging() );

    graphEdge::sptr edge;

    try
    {
        edge = parent -> addChild( componentNode::sptr( component ), index );
    }
    catch( ... )
    {
        fireEvent( projectChangesCancelled() );
        throw;
    }

    graphNode::nodeInfo retInfo( parent, edge );

    fireEvent( projectGraphNodeAdded( retInfo ) );

    return retInfo;
}

graphNode::nodeInfo project::addNewComponent ( long parentId, int index )
{
    //! @param index Index of position to place new component in. Use -1 to append to end of children.
    //! @param parentId Id of parent to add fragment to as a child.
    //!                 Use -1 to add to graph root.
    //! @return ID of Edge that links to newly created component.

    return addNewComponent( string(), parentId, index );
}

graphNode::nodeInfo project::addNewFragment ( const string& fragName, long parentId, int index )
{
    //! @param fragName New fragments name.
    //! @param parentId Id of parent to add fragment to as a child.
    //!                 Use -1 to add to graph root.
    //! @param index Index of position to place new fragment in. Use -1 to append to end of children.
    //! @param return Node ID of newly created fragment or error code.
    //! @throw NameInUse If name is already used within project.

    string nodeName;

    // Generate a name if none provided.
    
    if ( fragName.empty() )
    {
        nodeName = generate_next_name( "fragment", graph_root );
    }
    else
        nodeName = fragName;

    if ( nameInUse( graph_root, fragName ) ) throw stk::NameInUse();

    graphNode::sptr parent;

    // Find parent node.

    if ( parentId > -1 )
    {
        parent = stk::findNodeFromId( graph_root, parentId );
    }
    else
        parent = graph_root;

    fragmentNode* newFrag = new fragmentNode( nodeName );

    newFrag -> addEventListener( this );
    
    fireEvent( projectChanging() );

    graphEdge::sptr edge;

    try
    {
        edge = parent -> addChild( fragmentNode::sptr( newFrag ), index );
    }
    catch( ... )
    {
        fireEvent( projectChangesCancelled() );
        throw;
    }

    graphNode::nodeInfo retInfo( parent, edge );

    fireEvent( projectGraphNodeAdded( retInfo ) );

    return retInfo;
}

graphNode::nodeInfo project::addNewFragment ( long parentId, int index )
{
    //! @param parentId Id of parent to add fragment to as a child.
    //!                 Use -1 to add to graph root.
    //! @param index Index of position to place new fragment in. Use -1 to append to end of children.
    //! @param return Node ID of newly created fragment or error code.

    return addNewFragment( string(), parentId, index );
}

graphNode::nodeInfo project::addNewPoint ( const string& pointName, long parentId, const string& exprX,
                                           const string& exprY, const string& exprZ, const string& exprW, int index )
{
    //! @param pointName New points name.
    //! @param parentId Id of parent to add point to as a child.
    //!                 Use -1 to add to project root.
    //! @param exprX Expression for x component of point.
    //! @param exprY Expression for y component of point.
    //! @param exprZ Expression for z component of point.
    //! @param exprW Expression for w component of point.
    //! @param index Index of position to place new point in. Use -1 to append to end of children.
    //! @throw NameInUse If name is already used within project.

    string nodeName;

    // Generate a name if none provided.
    
    if ( pointName.empty() )
    {
        nodeName = generate_next_name( "point", graph_root );
    }
    else
        nodeName = pointName;

    if ( nameInUse( graph_root, nodeName ) ) throw stk::NameInUse();

    graphNode::sptr parent;

    // Find parent node.

    if ( parentId > -1 )
    {
        parent = findNodeFromId( graph_root, parentId );
    }
    else
        parent = graph_root;

    pointNode* newPoint = new pointNode( nodeName, exprX, exprY, exprZ, exprW );

    newPoint -> addEventListener( this );
    
    fireEvent( projectChanging() );

    graphEdge::sptr edge;

    try
    {
        edge = parent -> addChild( pointNode::sptr( newPoint ), index );
    }
    catch( ... )
    {
        fireEvent( projectChangesCancelled() );
        throw;
    }

    graphNode::nodeInfo retInfo( parent, edge );

    fireEvent( projectGraphNodeAdded( retInfo ) );

    evaluate();

    return retInfo;
}

graphNode::nodeInfo project::addNewPoint ( long parentId, int index )
{
    //! @param parentId Id of parent to add point to as a child.
    //!                 Use -1 to add to project root.
    //! @param index Index of position to place new point in. Use -1 to append to end of children.

    return addNewPoint( string(), parentId, string(), string(), string(), string(), index );
}

graphNode::nodeInfo project::addNewParam ( const string& paramName, long parentId,
                                           const string& paramExpr, int index )
{
    //! @param parentId Id of parent to add point to as a child. Use -1 to add to project root.
    //! @param paramName Name of parameter.
    //! @param paramExpr Expression that defines parameter value.
    //! @param index Index of position to place new point in. Use -1 to append to end of children.
    //! @throw NameInUse If name is already used within project.

    string nodeName;

    // Generate a name if none provided.
    
    if ( paramName.empty() )
    {
        nodeName = generate_next_name( "param", graph_root );
    }
    else
        nodeName = paramName;

    if ( nameInUse( graph_root, nodeName ) ) throw stk::NameInUse();

    graphNode::sptr parent;

    // Find parent node.

    if ( parentId > -1 )
    {
        parent = findNodeFromId( graph_root, parentId );
    }
    else
        parent = graph_root;

    // Create, add and evaluate.

    paramNode* newParam;

    if ( ! paramExpr.empty() )
        newParam = new paramNode( nodeName, paramExpr );
    else
        newParam = new paramNode( nodeName );

    newParam -> addEventListener( this );
    
    fireEvent( projectChanging() );

    graphEdge::sptr edge;

    try
    {
        edge = parent -> addChild( paramNode::sptr( newParam ), index );
    }
    catch( ... )
    {
        fireEvent( projectChangesCancelled() );
        throw;
    }

    graphNode::nodeInfo retInfo( parent, edge );

    fireEvent( projectGraphNodeAdded( retInfo ) );

    evaluate();

    return retInfo;
}

graphNode::nodeInfo project::addNewParam ( long parentId, int index )
{
    //! @param parentId Id of parent to add point to as a child. Use -1 to add to project root.
    //! @param index Index of position to place new point in. Use -1 to append to end of children.

    return addNewParam( string(), parentId, string(), index );
}

graphNode::nodeInfo project::moveNode ( long nodeToMoveEdgeId, graphNode::sptr newParent, int newIndex )
{
    //! @param nodeToMoveEdgeId The Edge ID of node to move.
    //! @param newParent Node that is to be the new parent.
    //! @param newIndex Child index to move node to.

    graphNode::sptr parent = newParent;

    if ( parent.isNull() )
        parent = graph_root;

    // Find node to move.
    
    graphNode::nodeInfo toMoveInfo;

    try
    {
        toMoveInfo = graphNode::nodeInfo( stk::findNodeFromEdgeId( graph_root, nodeToMoveEdgeId ) );
    }
    catch( stk::NodeNotFound )
    {
        throw ActionCancelled();
    }

    // Add node to new parent.

    graphEdge::sptr edge;

    fireEvent( projectChanging() );

    try
    {
        edge = parent -> addChild( toMoveInfo.node(), newIndex );
    }
    catch( graphNode::NotPermitted )
    {
        fireEvent( projectChangesCancelled() );
        throw ActionCancelled();
    }
    catch( ... )
    {
        fireEvent( projectChangesCancelled() );
        throw;
    }

    graphNode::nodeInfo newInfo( parent, edge );

    fireEvent( projectGraphNodeAdded( newInfo ) );

    // Remove node from current parent.

    fireEvent( projectChanging() );

    int edgeIndex;

    try
    {
        edgeIndex = ( toMoveInfo.parent() ) -> childIndex( nodeToMoveEdgeId ); // Must get current child index of edge.
        ( toMoveInfo.parent() ) -> removeChild( nodeToMoveEdgeId );
    }
    catch( graphNode::EdgeNotFound )
    {
        fireEvent( projectChangesCancelled() );
        throw ActionCancelled();
    }
    catch( ... )
    {
        fireEvent( projectChangesCancelled() );
        throw;
    }

    fireEvent( projectGraphNodeRemoved( edgeIndex, toMoveInfo ) );

    evaluate();

    return newInfo;
}

graphNode::nodeInfo project::moveNode ( long nodeToMoveEdgeId, long newParentId, int newIndex )
{
    //! @param nodeToMoveEdgeId The Edge ID of node to move.
    //! @param newParentId ID of new parent node. Use -1 for no parent.
    //! @param newIndex Child index to move node to.

    return moveNode( nodeToMoveEdgeId, findNode( newParentId ), newIndex );
}

componentNode::listSptr project::getComponentList()
{
    //! @return Safe pointer to list of components.

    listGraphAction action( opensolid::graphNode::COMPONENT );

    action.apply( graph_root );

    graphNode::listSptr list = action.nodesFound();

    // Copy node list into a component list.

    componentNode::listSptr retList = componentNode::listSptr( new ptrList<componentNode::sptr>() );

    graphNode::sptr node = list -> first();

    while ( ! node.isNull() )
    {
        retList -> append( new componentNode::sptr( node ), true );
        node = list -> next();
    }

    return retList;
}

void project::dump()
{
    //! Dump graph to std out as simple text names.

    dumpGraphAction action( dumpGraphAction::TXT_NODE_NAMES_ONLY );

    action.apply( graph_root );
}

void project::graphNodeNameChanging ( int nodeId, const string& changingTo )
{
    // Node name changing event. Cancel if name is already in use.

    if ( nameInUse( graph_root, changingTo ) )
    {
        throw NameInUse();
    }
}

void project::graphNodeChanged ( int nodeId )
{
    // Evaluate the graph when a node changes.

    evaluate();

    // Re-package Node Changed event so that project listeners are notified.

    try
    {
        graphNode::sptr node = findNode ( nodeId );

        fireEvent( projectGraphNodeChanged( node ) );
    }
    catch( NodeNotFound )
    {
    }
}

bool project::nameInUse ( graphNode::sptr graphRoot, const string& nodeName )
{
    //! @param graphRoot Root node of graph to search.
    //! @param nodeName Node name to find.
    //! @return True if name exists in graph.

    try
    {
        graphNode::sptr nodeFound = stk::findNodeFromName( graphRoot, nodeName );
    }
    catch ( NodeNotFound )
    {
        return false;
    }

    return true; // If exception wasn't thrown then a node was found.
}

std::string project::generate_next_name ( std::string prefix, graphNode::sptr graphRoot )
{
    //! @param sect Project section to use.
    //! @param prefix Name prefix to use in front of numerical index.

    std::string name;

    int index = 1;

    do
    {
        std::stringstream nameStream;
        nameStream << prefix << index ++;
        name = nameStream.str();
        
    } while ( nameInUse( graphRoot, name.c_str() ) );

    return name;
}

}

