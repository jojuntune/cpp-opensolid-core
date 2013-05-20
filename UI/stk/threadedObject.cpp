// Copyright 2007 Scott Lanham
// ---------------------------
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

namespace stk
{

threadedObject::~threadedObject()
{
}

threadedObject::threadedObject()
{
    quit_thread = false;
}

int threadedObject::threadEntry()
{
    return 0;  // Don't do anything if a subclass has not re-implemented the thread entry point.
}

void threadedObject::quitThread ( bool yesNo )
{
    quit_thread = yesNo;
}

bool threadedObject::quitThread()
{
    return quit_thread;
}

bool threadedObject::lock()
{
    // Lock object using mutex.
    // ------------------------
    //
    // Notes:   Simple for now but could do more complex error cleanup.
    
    return mutex.lock();
}

bool threadedObject::unlock()
{
    // Unlock objects mutex.
    // ---------------------
    
    return mutex.unlock();
}

bool threadedObject::wait()
{
    // Wait on condition.
    // ------------------
    //
    // Notes:    Object is in the locked state upon exit.
    
    if ( lock() )
        return cond.wait ( mutex );
        
    return false;
}

bool threadedObject::signal()
{
    // Wake up thread that is blocking on condition.
    // ---------------------------------------------
    
    return cond.signal();
}

}
