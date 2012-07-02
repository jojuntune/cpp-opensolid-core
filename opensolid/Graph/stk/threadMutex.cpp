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

#include "threadMutex.h"

namespace stk
{

threadMutex::threadMutex()
{
    qMutex = 0;
}

threadMutex::~threadMutex()
{
    if ( qMutex ) delete qMutex;
}

threadMutex::threadMutex ( const threadMutex& )
{
    qMutex = 0; // No need to create new mutex as it will be created when needed.
}

threadMutex& threadMutex::operator= ( const threadMutex& )
{
    // No need to create new qt mutex.

    return *this;
}

void threadMutex::init()
{
    if ( ! qMutex ) qMutex = new QMutex;
}

bool threadMutex::lock()
{
    // Returns true if successful.
    // ---------------------------

    init();
    
    qMutex -> lock();
    return true;
}

threadMutex::token threadMutex::lockToken()
{
    return token( this );
}

bool threadMutex::unlock()
{
    // Returns true if successful.
    // ---------------------------

    init();

    qMutex->unlock();
    return true;
}

}
