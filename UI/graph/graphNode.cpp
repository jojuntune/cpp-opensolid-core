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

#include <stk/NameInUse.h>

#include "graphNode.h"
#include "graphNodeEvents.h"
#include "nodeNameProperty.h"

namespace opensolid
{

graphNode::~graphNode()
{
}

graphNode::graphNode()
{
    init();
}

graphNode::graphNode ( const string& name )
    : stk::graphNode( name )
{
    init();
}

void graphNode::init()
{
    // Add node name property.

    addProperty( new nodeNameProperty<graphNode> ( "Name", this, &graphNode::name, &graphNode::name ) );
}

int graphNode::type()
{
    cout << "WARNING: Type requested from node not implementing type() function.\n";

    return NODE;
}

bool graphNode::visible()
{
    return is_visible;
}

void graphNode::visible ( bool trueFalse )
{
    is_visible = trueFalse;
}

bool graphNode::dirty()
{
    return is_dirty;
}

void graphNode::dirty ( bool trueFalse )
{
    is_dirty = trueFalse;
}

void graphNode::name ( const string& newName )
{
    if ( name() == newName ) return;

    // Fire event to indicate name is about to be changed.

    fireEvent( graphNodeNameChanging( id(), newName ) );

    // Invoke base class method.

    stk::graphNode::name( newName );

    // Fire event to indicate node has changed.

    fireEvent( graphNodeChanged( id() ) );
}

// Actions.

void graphNode::evaluate ( graphParamList::sptr )
{
    // Default behaviour is no action.
}

void graphNode::render ( int )
{
    // Default behaviour is no action.
}

} // namespace opensolid.
