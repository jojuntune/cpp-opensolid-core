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

#include "evaluateGraphAction.h"

namespace opensolid
{

evaluateGraphAction::evaluateGraphAction()
    : graphAction( true )
{
    paramList = graphParamList::sptr( new graphParamList() );
}

evaluateGraphAction::evaluateGraphAction ( evaluateGraphAction& copyFrom )
    : graphAction( copyFrom )
{
    paramList = graphParamList::sptr( copyFrom.paramList, true ); // Deep copy the parameter list so that changes
                                                                  // to parameters don't propagate back up the graph.
}

evaluateGraphAction* evaluateGraphAction::clone()
{
    return new evaluateGraphAction( *this );
}

int evaluateGraphAction::_type()
{
    return EVALUATE_GRAPH_ACTION;
}

void evaluateGraphAction::process ( graphNode::nodeInfo& info, int traversalType )
{
    if ( traversalType == ASCEND ) return; // Descend graph only.

    (info.node()) -> evaluate( paramList );
}

}
