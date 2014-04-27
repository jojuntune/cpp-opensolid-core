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

#include "event.h"
#include "eventDispatcher.h"
#include "eventListener.h"

namespace stk
{

eventDispatcher::~eventDispatcher()
{
    {
        threadMutex::token listenerLock = listener_mutex.lockToken();
        threadMutex::token queueLock = queue_mutex.lockToken();
        
        eventListener* listener = event_listeners -> first();

        while ( listener )
        {
            listener -> removeDispatcher( this );
            listener = event_listeners -> next();
        }

        delete event_listeners;
        delete event_queue;
    }
}

eventDispatcher::eventDispatcher()
{
    event_listeners = new ptrList< eventListener >();

    event_queue = new ptrList< event >();

    _processing = false;
}

void eventDispatcher::addEventListener ( eventListener* listener )
{
    //! @param listener Event listener to dispatch events to.

    threadMutex::token token = listener_mutex.lockToken();
    
    event_listeners -> append( listener, false );
}

void eventDispatcher::removeEventListener ( eventListener* listener )
{
    //! @param listener Event listener to remove.

    threadMutex::token token = listener_mutex.lockToken();

    event_listeners -> remove( listener );
}

void eventDispatcher::fireEvent ( const event& eventToFire )
{
    //! @param eventToFire Event to invoke on event listeners.
    //! @par Notes This function may put the burden of processing one threads event on another thread.
    //!            Because event dispatching is done on a per object basis and not centrally, this shouldn't
    //!            be a performance problem.

    { threadMutex::token token = queue_mutex.lockToken();

        // Add event to queue.

        event_queue -> append( eventToFire.clone(), true );

        // If queue is already being processed then return.

        if ( _processing ) return;

        _processing = true;
    }

    // Process queued events.

    bool process = true;

    while ( process )
    {
        // Get event to process from queue.

        event* eventToProcess;

        { threadMutex::token token = queue_mutex.lockToken();

            eventToProcess = event_queue -> first();

            if ( ! eventToProcess )
            {
                process = false;
                _processing = false;
            }
        }

        // Process event.

        if ( process )
        {
            threadMutex::token token = listener_mutex.lockToken();

            eventListener* listener = event_listeners -> first();

            while ( listener )
            {
                if ( ! eventToProcess -> invoke( listener ) )
                    break; // Cancel event propogation.

                listener = event_listeners -> next();
            }

            // Remove event from queue.

            { threadMutex::token token = queue_mutex.lockToken();

                event_queue -> remove( eventToProcess );
            }
        }
    }
}

}
