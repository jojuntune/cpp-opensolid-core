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

#include "eventDispatcher.h"
#include "eventListener.h"

namespace stk
{

eventListener::~eventListener()
{
    eventDispatcher* disp = listens_to -> first();

    while ( disp )
    {
        disp -> removeEventListener( this );
        disp = listens_to -> next();
    }

    delete listens_to;
}

eventListener::eventListener()
{
    listens_to = new ptrList< eventDispatcher >();
}

//! Associate this listener with a dispatcher.
void eventListener::addDispatcher ( eventDispatcher* dispatcher )
{
    //! @param dispatcher Event dispatcher this event is connected to.

    threadMutex::token token = mutex.lockToken();

    if ( token.locked() )
        listens_to -> append( dispatcher, false );
}

//! Disassociate this listener from a dispatcher.
void eventListener::removeDispatcher ( eventDispatcher* dispatcher )
{
    //! @param dispatcher Event dispatcher this event is connected to.

    threadMutex::token token = mutex.lockToken();

    if ( token.locked() )
        listens_to -> remove( dispatcher );
}

}
