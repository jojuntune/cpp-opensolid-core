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

#ifndef STK_GRAPH_FINDACTION_H
#define STK_GRAPH_FINDACTION_H

#include "graphAction.h"
#include "graphNode.h"

namespace stk
{

class findGraphAction : public graphAction
{
    public:
        
        findGraphAction();

        findGraphAction ( long edgeId ); //!< Find graph node given an edge ID.

        findGraphAction ( const string& nodeName ); //!< Find graph node given nodes name.

        virtual findGraphAction* clone();

        void findNodeFromEdgeId ( long edgeId ); //!< Set Edge ID to find.
        
        void findNodeFromNodeId ( long nodeId ); //!< Set Node ID to find.

        void findNodeFromName ( const string& nodeName ); //!< Find graph node given a node name.

        graphNode::sptr nodeFound(); //!< Return safe pointer to node that was found.
        graphNode::sptr nodeFoundParent(); //!< Return safe pointer to parent of the node found.
        graphNode::nodeInfo nodeFoundInfo(); //!< Return nodeInfo struct with node found details.

        enum findType
        {
            EDGE_ID,
            NODE_ID,
            NODE_NAME
        };

    protected:

        virtual int _type();

        virtual void process ( graphNode::nodeInfo& info, int traversalType );

    private:

        void clear(); //!< Clear found node info ready for new search.

        void findNodeFromEdgeId ( graphNode::nodeInfo& info );
        void findNodeFromNodeId ( graphNode::nodeInfo& info );
        void findNodeFromName ( graphNode::nodeInfo& info );

        int         find_type;

        int         edge_id_toFind;

        int         node_id_toFind;

        string      node_name_toFind;
        
        graphNode::nodeInfo node_found_info;

        int         node_childIndex_found;
};

}

#endif
