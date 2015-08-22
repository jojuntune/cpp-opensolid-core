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

#include "listGraphAction.h"

namespace opensolid
{

listGraphAction::~listGraphAction()
{
}

listGraphAction::listGraphAction()
    : graphAction( false )
{
    type_to_list = -1;
    init();
}

void listGraphAction::copy_from ( listGraphAction& copyFrom )
{
    type_to_list = copyFrom.type_to_list;

    list = copyFrom.list;  // Share list between multiple list actions to allow for distributed processing.
}

listGraphAction::listGraphAction ( listGraphAction& copyFrom )
    : graphAction( copyFrom )
{
    copy_from( copyFrom );
}

listGraphAction& listGraphAction::operator= ( listGraphAction& copyFrom )
{
    copy_from( copyFrom );

    return *this;
}

listGraphAction::listGraphAction ( int listType )
    : graphAction( false )
{
    type_to_list = listType;
    init();
}

listGraphAction* listGraphAction::clone()
{
    return new listGraphAction( *this );
}

void listGraphAction::init()
{
    list = graphNode::listSptr( new ptrList<graphNode::sptr>() );
}

void listGraphAction::process ( graphNode::nodeInfo& info, int traversalType )
{
    if ( traversalType == ASCEND ) return;
    
    if ( type_to_list == -1 || (info.node()) -> type() == type_to_list )
    {
        THREAD_SYNC
        list -> append ( new graphNode::sptr( info.node() ), true );
    }
}

graphNode::listSptr listGraphAction::nodesFound()
{
    //! @return Reference to list of nodes found by this action.

    return list;
}

int listGraphAction::_type()
{
    return LIST_GRAPH_ACTION;
}

}
