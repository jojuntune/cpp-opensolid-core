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

#include "graphAction.h"

namespace opensolid
{

graphAction::~graphAction()
{
}

graphAction::graphAction( bool cloneOnDescend, bool singleThread )
    : stk::graphAction( cloneOnDescend, singleThread )
{
    //! @param cloneOnDescend Clone this action to descend into child nodes of current node being acted upon.
}

int graphAction::type()
{
    return _type() + MAX_STK_ACTION; // Make sure stk action types are not overlapped.
}

void graphAction::process ( stk::graphNode::nodeInfo& info, int traversalType )
{
    opensolid::graphNode::nodeInfo translatedInfo = info;
    
    process ( translatedInfo, traversalType );
}

}
