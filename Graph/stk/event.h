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

#ifndef STK_EVENT_H
#define STK_EVENT_H

namespace stk
{

class eventListener;

//! Base class for an event.

class event
{
    public:

        //! Invoke event on event listener.
        //! @return False to cancel event otherwise True.
        virtual bool invoke( eventListener* ) const = 0;

        //! Require all subclasses to have a clone method.
        virtual event* clone() const = 0;
};

}

#endif
