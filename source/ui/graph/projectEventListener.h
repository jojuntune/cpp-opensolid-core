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

#ifndef OS_PROJECT_EVENT_LISTENER_H
#define OS_PROJECT_EVENT_LISTENER_H

#include <stk/eventListener.h>

#include "graphNode.h"

namespace opensolid
{

class projectEventListener : public stk::eventListener
{
    public:

        virtual ~projectEventListener() {}
        
        //! Event to indicate project is about to change.
        virtual void projectChanging() {}

        //! Event to indicate project is about to change.
        virtual void projectChangesCancelled() {}

        //! Event to indicate a graph node has been changed.
        //! @par Parameters
        //! Param: node. Safe pointer to node that triggered this event.
        virtual void projectGraphNodeChanged ( graphNode::sptr /*node*/ ) {}

        //! Event to indicate a graph node has been added to project.
        //! @par Parameters
        //! Param: info. Node information on node that has been added.
        virtual void projectGraphNodeAdded ( graphNode::nodeInfo /*info*/ ) {}

        //! Event to indicate a graph node has been removed from project.
        //! @par Parameters
        //! Param: edgeIndex. Child index of edge being removed.
        //! Param: info. Node information on node that has been removed.
        virtual void projectGraphNodeRemoved ( int /*edgeIndex*/, graphNode::nodeInfo /*info*/ ) {}

        //! Event to indicate a graph controlled by the project has been evaluated.
        //! @par Parameters
        virtual void projectGraphEvaluated() {}
};

}

#endif
