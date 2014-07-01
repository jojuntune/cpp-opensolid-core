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

#ifndef STK_GRAPH_ACTION_H
#define STK_GRAPH_ACTION_H

#include <bitset>

using namespace std;

#include "graphEdge.h"
#include "graphNode.h"
#include "safePtr.h"
#include "threadedObject.h"

namespace stk
{

//! An graphAction is an object which transverses the graph and has the ability to manipulate nodes while doing so.

class graphAction : public threadedObject
{
    //! @par Notes Actions may be cloned during multi-threaded propogation through the graph.
    
    public:

        virtual ~graphAction();

        graphAction ( bool cloneOnDescend, bool singleThread = false );

        virtual graphAction* clone() = 0; //!< Create a deep copy of this object.

        virtual void apply ( graphNode::sptr node ); //!< Apply action to node and it's descendants
        virtual void apply ( graphNode::nodeInfo info ); //!< Apply action to node and it's descendants

        bool active();

        enum traversalTypes
        {
            DESCEND,
            ASCEND
        };

        //! Action types.
        
        enum actionTypes
        {
            FIND_GRAPH_ACTION,
            DUMP_GRAPH_ACTION,
            MAX_STK_ACTION
        };

        //! Return actions type.
        virtual int type();

        //! Return actions type as a bit field.
        virtual actionTypeBitField typeBits(); // actionTypeBitField is defined in graphEdge.h.

        //! Calculate action type bit field given action type.
        static actionTypeBitField typeBits( int actionType );
    
    protected:

        virtual int _type() = 0; //! Get type from sub class.

        //! Process a node. Implementation MUST be re-entrant.
        virtual void process ( graphNode::nodeInfo& info, int traversalType ) = 0;

        void active ( bool yesNo ); //!< Set actions active state.

    private:

        bool    is_active; //!< If true action is active.

        bool    clone_on_descend; //!< If true, clone this action to descend into child nodes.

        bool    single_thread; //!< If true, only use a single thread for action graph traversal.
};

}

#endif
