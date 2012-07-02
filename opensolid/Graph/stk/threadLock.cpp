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

#include "threadedObject.h"
#include "threadLock.h"

namespace stk
{

threadLock::~threadLock()
{
    release();
}

threadLock::threadLock( threadedObject* object )
{
    //! @param object Threaded object that has not yet been locked.
    
    locked_object = object;

    if ( object -> lock() )
        is_locked = true;
    else
        is_locked = false;
}

void threadLock::release()
{
    if ( locked_object && is_locked )
    {
        locked_object -> unlock();
        is_locked = false;
    }
}

}
