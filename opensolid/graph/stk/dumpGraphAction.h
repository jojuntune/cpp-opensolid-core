// Copyright 2008 Scott Lanham.
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

#ifndef STK_GRAPH_DUMPACTION_H
#define STK_GRAPH_DUMPACTION_H

#include "graphAction.h"
#include "graphNode.h"

namespace stk
{

class dumpGraphAction : public graphAction
{
    public:

        dumpGraphAction ( int dumpType );

        virtual dumpGraphAction* clone();

        enum dumpType
        {
            TXT_NODE_NAMES_ONLY
        };

    protected:

        virtual int _type();

        virtual void process ( graphNode::nodeInfo& info, int traversalType );

    private:

        //!< Dump the name of a node to std out as simple text.
        void dumpTxtName( graphNode::nodeInfo& info, int indentLevel );

        int     dump_type;
        int     _level; //! Number of levels of graph that have been traversed.

};

}

#endif

