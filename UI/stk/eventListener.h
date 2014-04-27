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

#ifndef STK_EVENT_LISTENER_H
#define STK_EVENT_LISTENER_H

#include "ptrList.h"
#include "threadMutex.h"

//! Base class for event receival.

namespace stk
{

class eventDispatcher;

class eventListener
{
    public:

        virtual ~eventListener();

        eventListener();

        //! Associate this listener with a dispatcher.
        void addDispatcher ( eventDispatcher* dispatcher );

        //! Disassociate this listener from a dispatcher.
        void removeDispatcher ( eventDispatcher* dispatcher );

    private:

        threadMutex     mutex; // For sync independent of sub class threads.

        ptrList< eventDispatcher >* listens_to;
};

}

#endif
