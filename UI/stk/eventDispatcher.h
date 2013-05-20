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

#ifndef STK_EVENT_DISPATCHER_H
#define STK_EVENT_DISPATCHER_H

#include "ptrList.h"
#include "threadMutex.h"

//! Base class for an event dispatcher.

namespace stk
{

class eventListener;

class event;

class eventDispatcher
{
    public:

        virtual ~eventDispatcher();

        eventDispatcher();

        //! Add event listener to dispatcher.
        virtual void addEventListener ( eventListener* listener );

        //! Remove event listener from dispatcher.
        virtual void removeEventListener ( eventListener* listener );

        void fireEvent ( const event& eventToFire );

    private:

        threadMutex     listener_mutex;
        threadMutex     queue_mutex;

        ptrList< eventListener >* event_listeners;

        ptrList< event >* event_queue;

        bool    _processing; // True if the event queue is being procesed.
};

}

#endif
