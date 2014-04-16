// Copyright 2007 Scott A.E. Lanham
// --------------------------------
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.

#include "graphEdge.h"
#include "graphNode.h"

namespace stk
{

graphEdge::graphEdge()
    : action_filter( 0 )
{
}

graphEdge::graphEdge ( const string& edgeName, safePtr< graphNode > linkTo )
    : action_filter( 0 )
{
    name ( edgeName );
    link_to = linkTo;
}

safePtr< graphNode > graphEdge::link()
{
    return link_to;
}

void graphEdge::setActionFilter ( actionTypeBitField actionTypes )
{
    //! @param actionType Bit field selecting action types to add filters for.

    action_filter |= actionTypes;
}

void graphEdge::resetActionFilter ( actionTypeBitField actionTypes )
{
    //! @param actionType Bit field selecting action types to remove filters for.

    action_filter &= (~ actionTypes); // Clear bits for action types.
}

bool graphEdge::canTraverse ( actionTypeBitField actionType )
{
    return ( action_filter & actionType ) == 0;
}

}
