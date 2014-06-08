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

#ifndef OS_GRAPH_NODE_EVENT_LISTENER_H
#define OS_GRAPH_NODE_EVENT_LISTENER_H

#include <string>
using namespace std;

#include <stk/eventListener.h>

#include "propertyError.h"

namespace opensolid
{

class graphNodeEventListener : public stk::eventListener
{
    public:

        virtual ~graphNodeEventListener() {}

        //! Event to indicate a graph node is changing it's name.
        //! @par Parameters
        //! Param: nodeId. ID of node that triggered this event.
        //! Param: changingTo. String name is changing to.

        virtual void graphNodeNameChanging ( int /*nodeId*/, const string& /*changingTo*/ ) {}

        //! Event to indicate a graph node has changed.
        //! @par Parameters
        //! Param: nodeId. ID of node that triggered this event.
        virtual void graphNodeChanged ( int /*nodeId*/ ) {}

        //! Event to indicate an error occured with one of the nodes properties.
        //! @par Parameters
        //! Param: nodeId. ID of node that triggered this event.
        //! Param: propertyIndex. Index of the node property that has error.
        
        virtual void graphNodePropertyError ( const propertyError& error ) {}
};

}

#endif
