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

#include "threadCond.h"

namespace stk
{

threadCond::threadCond()
{
    cond = 0; // Don't use up memory unless it is needed.
}

threadCond::~threadCond()
{
    if ( cond ) delete cond;
}

threadCond::threadCond ( const threadCond& )
{
    cond = 0;
}

threadCond& threadCond::operator= ( const threadCond& )
{
    // There is no need to create a new qt condition.

    return *this;
}

void threadCond::init()
{
    if ( ! cond ) cond = new QWaitCondition;
}

bool threadCond::signal()
{
    // Signal the condition to wake a thread.
    // --------------------------------------

    if ( ! cond ) return false;

    cond -> wakeOne();
    
    return true;
}

bool threadCond::broadcast()
{
    // Signal the condition to wake all threads.
    // -----------------------------------------

    if ( ! cond ) return false;

    cond -> wakeAll();
    
    return true;
}
        
bool threadCond::wait ( threadMutex& mutex )
{
    // Wait on a condition.
    // --------------------
    // mutex:   Mutex to process with.
    //
    // Notes:   Mutex must be locked before entry into this function.

    init();

    return cond -> wait( mutex.qMutex );
}

bool threadCond::waitTimeout ( threadMutex& mutex, int timeout )
{
    // Wait on a condition with a timeout.
    // -----------------------------------
    // mutex:   Mutex to process with.
    // timeout: Time to wait.
    //
    // Notes:   Mutex must be locked before entry into this function.

    init();

    return cond -> wait( mutex.qMutex, timeout );
}

}
