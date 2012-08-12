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

#ifndef STK_GRAPHNODE_H
#define STK_GRAPHNODE_H

#include <iostream>
using namespace std;

#include "ptrList.h"

#include "Exception.h"
#include "graphEdge.h"
#include "namedObject.h"
#include "propertiedObject.h"
#include "safePtr.h"
#include "threadedObject.h"
#include "uniqueObject.h"

namespace stk
{

class graphNode : public namedObject, public uniqueObject, public propertiedObject
{
    //! @par Notes Child indexes start from 0.
    
    public:

        typedef safePtr<graphNode> sptr;
        typedef safePtr< ptrList<sptr> > listSptr;

        virtual ~graphNode();
    
        graphNode();

        graphNode ( const string& name );

        graphNode ( graphNode& copyFrom );
        graphNode& operator= ( graphNode& copyFrom );

        //! Graph Node Information
        class nodeInfo
        {
            public:

                nodeInfo(){};

                nodeInfo( sptr parent, graphEdge::sptr edge )
                    : _node( edge -> link() ), _parent( parent ), _edge( edge ){}

                nodeInfo( sptr node, sptr parent, graphEdge::sptr edge )
                    : _node( node ), _parent( parent ), _edge( edge ){}

                sptr node() { return _node; } //!< Return node that this information is about.
                sptr parent() { return _parent; } //!< Return parent of node.
                graphEdge::sptr edge() { return _edge; } //!< Return edge that links parent to node.

                long nodeId() { return _node -> id(); }
                long parentId() { return _parent -> id(); }
                long edgeId() { return _edge -> id(); }
                
            protected:
                
                sptr    _node; // Node that information is for.
                sptr    _parent; // Parent node that holds graph edge to node.
                graphEdge::sptr _edge; // Edge that defines link from parent to node.
        };

        //! Add child node into graph with this node as parent.
        graphEdge::sptr addChild ( sptr node, const string& linkName = "" );
        //! Add child node into graph with this node as parent.
        graphEdge::sptr addChild ( sptr node, int index, const string& linkName = "" );
        //! Insert child node into graph with this node as parent.
        graphEdge::sptr insertChild ( sptr node, int index, const string& linkName = "" );
        //! Remove child node link from this node.
        graphEdge::sptr removeChild ( long edgeId );
        //! Remove all child nodes from this node.
        void removeAllChildren();
        //! Move child of this object to different index.
        void moveChild ( int oldIndex, int newIndex );
        //! Find index of child node given it's edge ID.
        int childIndex ( long edgeId );
        //! Confirm existence of child node given it's edge ID.
        bool hasChild ( long edgeId );
        //! Confirm existence of child node given it's ID and index.
        bool hasChild ( long nodeId, int index );

        //! Get number of children this node has.
        int childCount();
        //! Return safe pointer to child node.
        sptr childAtIndex ( int index );
        //! Return edge at given index.
        graphEdge::sptr edgeAtIndex ( int index );
        
        //! Generate list of children.
        listSptr getChildList();
        
        //! Generate a copy of the list of edges this node has.
        graphEdge::listSptr getEdgeList();

        // Exceptions. ( Use first letter capitalised for exception class ).

        //! Exception thrown to indicate a requested edge was not found.
        class EdgeNotFound : public Exception { public: EdgeNotFound( long edge_id ){ edgeId = edge_id;}
                                                        long edgeId; };

        //! Exception thrown to indicate requested action is not permitted.
        class NotPermitted : public Exception {};

    protected:

        void init();
    
    private:

        void copy ( graphNode& copyFrom );
        
        graphEdge::sptr* findEdge ( long edgeId ); //!< Find edge given its ID.
        int findEdgeIndex ( long edgeId ); //!< Find first edge index that links to node.

        ptrList <graphEdge::sptr> children;
};

}

#endif
