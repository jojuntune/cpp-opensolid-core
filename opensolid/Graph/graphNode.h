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

#ifndef GRAPH_NODE_H
#define GRAPH_NODE_H

#define maxNameLen 1024
#define maxExprLen 2048

#include <iostream>
using namespace std;

#include <stk/eventDispatcher.h>
#include <stk/graphNode.h>
#include <stk/ptrList.h>
using namespace stk;

#include "graphParamList.h"

namespace opensolid
{

class graphNode : public stk::graphNode, public stk::eventDispatcher
{
    public:

        typedef safePtr<graphNode> sptr;
        typedef safePtr< ptrList<sptr> > listSptr;

        virtual ~graphNode();
    
        graphNode(); //!< Default constructor.

        graphNode ( const string& name );

        void init(); //!< Initialise graph node.

        //! Graph Node Information
        class nodeInfo : public stk::graphNode::nodeInfo
        {
            public:

                nodeInfo(){};

                nodeInfo( sptr parent, graphEdge::sptr edge )
                    : stk::graphNode::nodeInfo( parent, edge ){}

                nodeInfo( sptr node, sptr parent, graphEdge::sptr edge )
                    : stk::graphNode::nodeInfo( node, parent, edge ){}

                nodeInfo( const stk::graphNode::nodeInfo& copyFrom )
                    : stk::graphNode::nodeInfo( copyFrom ){}

                graphNode::sptr node() { return _node; } //!< Return node that this information is about.
                graphNode::sptr parent() { return _parent; } //!< Return parent of node.
                graphEdge::sptr edge() { return _edge; } //!< Return edge that links parent to node.
        };

        enum types
        {
            NODE,
            PROJECT,
            GROUP,
            COMPONENT,
            FRAGMENT,
            POINT,
            CURVE,
            SURFACE,
            ASSEMBLY,
            PARAMETER
        };

        virtual int type();
        
        bool visible(); //!< Get visible state of node.
        void visible ( bool isVisible ); //!< Set visible state of node.

        bool dirty(); //!< Get state of nodes dirty flag.
        void dirty ( bool trueFalse ); //!< Set state of nodes dirty flag.

        virtual void name ( const string& newName ); //!< Set nodes name.
        virtual string name() { return stk::graphNode::name(); } //!< Get nodes name.

        // Exceptions.
        

        // Actions.

        virtual void evaluate ( graphParamList::sptr paramList ); //!< Expression evaluation.

        enum renderTypes { RENDER_APPLY, RENDER_RESTORE };
        
        virtual void render ( int renderType ); //!< Render to current OpenGL context.

    protected:
    
    private:

        bool    is_visible;

        bool    is_dirty;
    
};

}

#endif
