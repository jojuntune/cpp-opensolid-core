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

#include "dumpGraphAction.h"

namespace stk
{

dumpGraphAction::dumpGraphAction ( int dumpType )
    : graphAction( false, true )
{
    dump_type = dumpType;

    _level = -1;
}

dumpGraphAction* dumpGraphAction::clone()
{
    return new dumpGraphAction( *this );
}

void dumpGraphAction::process ( graphNode::nodeInfo& info, int traversalType )
{
    //! @param info Information about node to process.
    //! @param traversalType Type of graph traversal.
    
    if ( traversalType == ASCEND )
    {
        _level --;
    }
    else
    {
        _level ++;
        
        switch ( dump_type )
        {
            case TXT_NODE_NAMES_ONLY:
                dumpTxtName( info, _level );
                break;
        }
    }
}

int dumpGraphAction::_type()
{
    return DUMP_GRAPH_ACTION;
}

void dumpGraphAction::dumpTxtName ( graphNode::nodeInfo& info, int indentLevel )
{
    //! @param info Info of node to dump name of.
    //! @param indentLevel Indent level.

    for ( int count = 0; count < indentLevel; count ++ )
        cout << "\t";

    cout << (( info.node() ) -> name() ) << "\n";
}

}
