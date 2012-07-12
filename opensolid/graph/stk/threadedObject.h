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

#ifndef STK_THREADEDOBJECT_H
#define STK_THREADEDOBJECT_H

#include "threadLock.h"
#include "threadMutex.h"
#include "threadCond.h"

// This locking regime is both exception and codeBlock return safe.
#define THREAD_SYNC stk::threadLock __lockObject( this );

namespace stk
{

class threadedObject
{
    public:

        virtual ~threadedObject();
        threadedObject();
    
        virtual int threadEntry();  // Standard thread entry function.
        
        void quitThread ( bool yesNo );
        
        bool quitThread();
        
        virtual bool wait();
        
        virtual bool signal();
    
        virtual bool lock();
        
        virtual bool unlock();
        
    private:
    
        bool            quit_thread;  // Quit thread started by thread();
        
        threadMutex     mutex;  // Standard Mutex. Used for locking object.
        
        threadCond      cond;  // Standard condition. Used for blocking.
};

}

#endif
