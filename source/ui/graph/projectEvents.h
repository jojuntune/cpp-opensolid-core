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

#ifndef OS_PROJECT_EVENTS_H
#define OS_PROJECT_EVENTS_H

#include <stk/event.h>

#include "projectEventListener.h"

namespace opensolid
{

//! Project graph node changed event.
class projectGraphNodeChanged : public stk::event
{
    public:

        projectGraphNodeChanged ( graphNode::sptr node )
            : _node( node ) {}

        event* clone() const { return new projectGraphNodeChanged( *this ); }

        bool invoke ( eventListener* listener ) const
        {
            ((projectEventListener*) listener) -> projectGraphNodeChanged( _node );

            return true; // Continue to propogate event.
        }

    private:
        
        graphNode::sptr _node;
};

//! Project changing event.
class projectChanging : public stk::event
{
    public:

        projectChanging() {}

        event* clone() const { return new projectChanging( *this ); }

        bool invoke ( eventListener* listener ) const
        {
            ((projectEventListener*) listener) -> projectChanging();

            return true;
        }

    private:
};

//! Project changes cancelled event.
class projectChangesCancelled : public stk::event
{
    public:

        projectChangesCancelled() {}

        event* clone() const { return new projectChangesCancelled( *this ); }

        bool invoke ( eventListener* listener ) const
        {
            ((projectEventListener*) listener) -> projectChangesCancelled();

            return true;
        }

    private:
};

//! Project graph node added event.
class projectGraphNodeAdded : public stk::event
{
    public:

        projectGraphNodeAdded ( graphNode::nodeInfo info )
            : _info( info ) {}

        event* clone() const { return new projectGraphNodeAdded( *this ); }

        bool invoke ( eventListener* listener ) const
        {
            ((projectEventListener*) listener) -> projectGraphNodeAdded( _info );

            return true;
        }

    private:
        
        graphNode::nodeInfo _info;
};

//! Project graph node removed event.
class projectGraphNodeRemoved : public stk::event
{
    public:

        projectGraphNodeRemoved ( int edgeIndex, graphNode::nodeInfo info )
            : edge_index( edgeIndex), _info( info ) {}

        event* clone() const { return new projectGraphNodeRemoved( *this ); }

        bool invoke ( eventListener* listener ) const
        {
            ((projectEventListener*) listener) -> projectGraphNodeRemoved( edge_index, _info );

            return true;
        }

    private:
        
        int edge_index;
        graphNode::nodeInfo _info;
};

//! Project graph has been evaluated event.
class projectGraphEvaluated : public stk::event
{
    public:

        projectGraphEvaluated() {}

        event* clone() const { return new projectGraphEvaluated( *this ); }

        bool invoke ( eventListener* listener ) const
        {
            ((projectEventListener*) listener) -> projectGraphEvaluated();

            return true;
        }

    private:
};

}

#endif
