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

#ifndef OS_GRAPH_NODE_EVENTS_H
#define OS_GRAPH_NODE_EVENTS_H

#include <stk/event.h>

#include "graphNodeEventListener.h"
#include "propertyError.h"

namespace opensolid
{

//! Graph node name changing event.
class graphNodeNameChanging  : public stk::event
{
    public:
    
        //! Constructor.
        //! @param nodeId ID of node that is changing.
        //! @param changingTo String nodes name is changing to.
        
        graphNodeNameChanging ( int nodeId, const string& changingTo )
            : node_id( nodeId), changing_to( changingTo ) {}

        event* clone() const { return new graphNodeNameChanging( *this ); }

        bool invoke ( stk::eventListener* listener ) const
        {
            ((graphNodeEventListener*) listener) -> graphNodeNameChanging( node_id, changing_to );

            return true; // Continue to propogate event.
        }

    private:

        int node_id;
        const string& changing_to;
};

//! Graph node changed event.
class graphNodeChanged : public stk::event
{
    public:

        //! Constructor.
        //! @param nodeId ID of node that is changing.
        
        graphNodeChanged ( int nodeId )
            : node_id( nodeId) {}

        event* clone() const { return new graphNodeChanged( *this ); }

        bool invoke ( stk::eventListener* listener ) const
        {
            ((graphNodeEventListener*) listener) -> graphNodeChanged( node_id );

            return true; // Continue to propogate event.
        }

    private:

        int node_id;
};

//! Graph node property error event.
class graphNodePropertyError : public stk::event
{
    public:

        //! Constructor.
        //! @param nodeId ID of node that is changing.
        //! @param propertyIndex Index of property that has error.
        
        graphNodePropertyError ( const propertyError& error )
            : property_error( error ) {}

        event* clone() const { return new graphNodePropertyError( *this ); }

        bool invoke ( stk::eventListener* listener ) const
        {
            ((graphNodeEventListener*) listener) -> graphNodePropertyError( property_error );

            return true; // Continue to propogate event.
        }

    private:

        propertyError property_error;
};

}

#endif
