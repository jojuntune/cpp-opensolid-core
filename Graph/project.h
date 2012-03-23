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

#ifndef PROJECT_H
#define PROJECT_H

#include <string>
using namespace std;

#include <stk/eventDispatcher.h>
#include <stk/safePtr.h>
using namespace stk;

#include "componentNode.h"
#include "Exception.h"
#include "graphScript.h"
#include "graphNode.h"
#include "graphNodeEventListener.h"

#define NO_PARENT -1

namespace opensolid
{

//! Base class of all projects.

class project : public namedObject, public graphNodeEventListener, public eventDispatcher
{
    public:

        typedef safePtr<project> sptr;

        virtual ~project(){};

        project ( const string& projectName );

        virtual void render();

        //! Find node given the edge ID of a link to the node.
        virtual graphNode::nodeInfo findNodeFromEdgeId ( int edgeId );

        //! Find graph node.
        virtual graphNode::sptr findNode ( const string& nodeName );

        //! Find graph node.
        virtual graphNode::sptr findNode ( int nodeId );

        //! Return root of project graph.
        virtual graphNode::sptr graphRoot();

        //! Evaluate a project graph.
        void evaluate();

        //! Generate new component and add to project.
        graphNode::nodeInfo addNewComponent ( const string& componentName, long parentId, int index = -1 );

        //! Generate new component and add to project.
        graphNode::nodeInfo addNewComponent ( long parentId, int index = -1 );

        //! Generate new fragment and add to project.
        graphNode::nodeInfo addNewFragment ( const string& fragName, long parentId, int index = -1 );

        //! Generate new fragment and add to project.
        graphNode::nodeInfo addNewFragment ( long parentId, int index = -1 );

        //! Generate new point and add to project.
        graphNode::nodeInfo addNewPoint ( const string& pointName, long parentId, const string& exprX,
                                          const string& exprY, const string& exprZ, const string& exprW,
                                          int index = -1 );

        //! Generate new point and add to project.
        graphNode::nodeInfo addNewPoint ( long parentId, int index = -1 );

        //! Generate a new parameter.
        graphNode::nodeInfo addNewParam ( const string& paramName, long parentId,
                                          const string& paramExpr, int index = -1 );

        //! Generate a new parameter with default values.
        graphNode::nodeInfo addNewParam ( long parentId, int index = -1 );

        //! Move node within a project graph.
        graphNode::nodeInfo moveNode ( long nodeToMoveEdgeId, graphNode::sptr newParent, int newIndex );

        //! Move node within project graph.
        graphNode::nodeInfo moveNode ( long nodeToMoveEdgeId, long newParentId, int newIndex );

        // Possibly deprecate.

        componentNode::listSptr getComponentList(); //!< Return a list of components in project.

        void dump(); //!< Dump contents of graph to std out.

        // Events.

        //! Listen for node name changing.
        void graphNodeNameChanging ( int nodeId, const string& changingTo );

        //! Listen for node changed.
        void graphNodeChanged ( int nodeId );

        // Exceptions. ( Use first letter capitalised for exception class ).

        class ActionCancelled : public stk::Exception {};

    protected:

        //! Return true if name has already been used.
        bool nameInUse ( graphNode::sptr graphRoot, const string& nodeName );

        //! Generate next available node name.
        string generate_next_name ( std::string prefix, graphNode::sptr sect );

    private:

        graphNode::sptr graph_root;
};

}

#endif
